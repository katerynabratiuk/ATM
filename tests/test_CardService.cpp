#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "backend/services/CardService.h"
#include "backend/enums/Exceptions.h"
#include "backend/models/Card.h"
#include "backend/core/Money.h"
#include "backend/external/libbcrypt/include/bcrypt/BCrypt.hpp"
#include "mocks/MockCardRepository.h"
#include "mocks/MockTransactionRepository.h"
#include "mocks/MockBanknoteService.h"

using ::testing::Return;
using ::testing::_;
using ::testing::Throw;
using ::testing::An;

class CardServiceTest : public ::testing::Test {
protected:
    MockCardRepository mockCardRepo;
    MockBanknoteService mockBanknoteService;
    MockTransactionRepository mockTxRepo;
    CardService cardService;

    std::string testCardNum = "1234567890123";
    std::string testPin = "1234";
    std::string validHash;
    Card testCard;

    CardServiceTest() : cardService(mockCardRepo, mockBanknoteService, mockTxRepo) {
        // Generate hash for PIN "1234"
        // We can't mock the static BCrypt::validatePassword function,
        // so we use the real BCrypt logic but with mocked data from the repository.
        validHash = BCrypt::generateHash(testPin, 12);

        testCard._cardNumber = testCardNum;
        testCard._pin = validHash;
        testCard._balance = atm::money::money(1000); // 1000.00
        testCard._creditLimit = atm::money::money(0); // Debit card
    }
};

// Test successful authentication
TEST_F(CardServiceTest, AuthSuccess) {
    EXPECT_CALL(mockCardRepo, doGetCard(testCardNum))
        .WillOnce(Return(testCard));

    // Expect the service to authenticate successfully
    EXPECT_NO_THROW(cardService.authenticate(testCardNum, testPin));
}

// Test failed authentication (incorrect PIN)
TEST_F(CardServiceTest, AuthFailureIncorrectPin) {
    EXPECT_CALL(mockCardRepo, doGetCard(testCardNum))
        .WillOnce(Return(testCard));

    // Expect AccessDenied exception
    EXPECT_THROW(cardService.authenticate(testCardNum, "wrongpin"), Exceptions::AccessDenied);
}

// Test successful deposit
TEST_F(CardServiceTest, DepositSuccess) {
    EXPECT_CALL(mockCardRepo, doGetCard(testCardNum))
        .WillOnce(Return(testCard));

    // Expect call to add balance
    EXPECT_CALL(mockCardRepo, doAddBalance(testCardNum, 500));

    // Expect creation of a successful transaction
    EXPECT_CALL(mockTxRepo, doCreateTransaction(An<Transaction>()))
        .WillOnce([](Transaction t) {
        EXPECT_EQ(t._fromCardNumber, "1234567890123");
        EXPECT_EQ(t._amount, 500);
        EXPECT_EQ(t._transactionType, TransactionType::DEPOSIT);
        EXPECT_EQ(t._transactionStatus, TransactionStatus::SUCCESSFUL);
            });

    cardService.deposit(testCardNum, 500);
}

// Test successful withdrawal (debit card)
TEST_F(CardServiceTest, WithdrawSuccessDebit) {
    EXPECT_CALL(mockCardRepo, doGetCard(testCardNum))
        .WillOnce(Return(testCard)); // Balance 1000

    // Expect call to dispense service
    EXPECT_CALL(mockBanknoteService, doDispense(200));

    // Expect call to subtract balance
    EXPECT_CALL(mockCardRepo, doSubtractBalance(testCardNum, 200));

    // Expect successful transaction
    EXPECT_CALL(mockTxRepo, doCreateTransaction(An<Transaction>()))
        .WillOnce([](Transaction t) {
        EXPECT_EQ(t._amount, 200);
        EXPECT_EQ(t._transactionType, TransactionType::WITHDRAWAL);
        EXPECT_EQ(t._transactionStatus, TransactionStatus::SUCCESSFUL);
            });

    cardService.withdraw(testCardNum, 200);
}

// Test failed withdrawal (not enough money)
TEST_F(CardServiceTest, WithdrawFailureNotEnoughMoney) {
    EXPECT_CALL(mockCardRepo, doGetCard(testCardNum))
        .WillOnce(Return(testCard)); // Balance 1000

    // Do NOT expect calls to doDispense or doSubtractBalance
    EXPECT_CALL(mockBanknoteService, doDispense(_)).Times(0);
    EXPECT_CALL(mockCardRepo, doSubtractBalance(_, _)).Times(0);

    // Expect failed transaction
    EXPECT_CALL(mockTxRepo, doCreateTransaction(An<Transaction>()))
        .WillOnce([](Transaction t) {
        EXPECT_EQ(t._amount, 2000);
        EXPECT_EQ(t._transactionStatus, TransactionStatus::FAILED);
            });

    // Attempt to withdraw 2000, having 1000
    EXPECT_THROW(cardService.withdraw(testCardNum, 2000), Exceptions::NotEnoughMoney);
}

// Test failed withdrawal (ATM cannot dispense amount)
TEST_F(CardServiceTest, WithdrawFailureNoSuchCash) {
    EXPECT_CALL(mockCardRepo, doGetCard(testCardNum))
        .WillOnce(Return(testCard)); // Balance 1000

    // Imitate error from BanknoteService
    EXPECT_CALL(mockBanknoteService, doDispense(200))
        .WillOnce(Throw(Exceptions::NoSuchCash));

    // Expect failed transaction
    EXPECT_CALL(mockTxRepo, doCreateTransaction(An<Transaction>()))
        .WillOnce([](Transaction t) {
        EXPECT_EQ(t._amount, 200);
        EXPECT_EQ(t._transactionStatus, TransactionStatus::FAILED);
            });

    EXPECT_THROW(cardService.withdraw(testCardNum, 200), Exceptions::NoSuchCash);
}

// Test successful transfer
TEST_F(CardServiceTest, TransferSuccess) {
    std::string recipientCardNum = "9876543210987";
    Card recipientCard;
    recipientCard._cardNumber = recipientCardNum;
    recipientCard._balance = atm::money::money(500);
    recipientCard._creditLimit = atm::money::money(0);

    // Setup mocks
    EXPECT_CALL(mockCardRepo, doGetCard(testCardNum)) // Sender
        .WillOnce(Return(testCard)); // Balance 1000
    EXPECT_CALL(mockCardRepo, doGetCard(recipientCardNum)) // Recipient
        .WillOnce(Return(recipientCard));

    // Expect actions
    EXPECT_CALL(mockCardRepo, doSubtractBalance(testCardNum, 300)); // Subtract from sender
    EXPECT_CALL(mockCardRepo, doAddBalance(recipientCardNum, 300)); // Add to recipient

    // Expect successful transaction
    EXPECT_CALL(mockTxRepo, doCreateTransaction(An<Transaction>()))
        .WillOnce([&](Transaction t) {
        EXPECT_EQ(t._fromCardNumber, testCardNum);
        EXPECT_EQ(t._toCardNumber, recipientCardNum);
        EXPECT_EQ(t._amount, 300);
        EXPECT_EQ(t._transactionStatus, TransactionStatus::SUCCESSFUL);
            });

    cardService.transfer(testCardNum, recipientCardNum, 300);
}

// Test failed transfer (to the same card)
TEST_F(CardServiceTest, TransferFailureSameCard) {
    // Do not expect any balance actions
    EXPECT_CALL(mockCardRepo, doSubtractBalance(_, _)).Times(0);
    EXPECT_CALL(mockCardRepo, doAddBalance(_, _)).Times(0);

    // Expect failed transaction
    EXPECT_CALL(mockTxRepo, doCreateTransaction(An<Transaction>()))
        .WillOnce([&](Transaction t) {
        EXPECT_EQ(t._fromCardNumber, testCardNum);
        EXPECT_EQ(t._toCardNumber, testCardNum);
        EXPECT_EQ(t._transactionStatus, TransactionStatus::FAILED);
            });

    EXPECT_THROW(cardService.transfer(testCardNum, testCardNum, 100), Exceptions::SameCard);
}