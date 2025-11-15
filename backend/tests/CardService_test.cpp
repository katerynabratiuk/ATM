#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "backend/services/CardService.h"
#include "backend/models/Card.h"
#include "backend/enums/Exceptions.h"
#include "backend/external/libbcrypt/include/bcrypt/BCrypt.hpp"
#include "mocks.h"

using ::testing::_;
using ::testing::Return;
using ::testing::Throw;
using ::testing::NiceMock;

class CardServiceTest : public ::testing::Test {
protected:
    // Mocks for all dependencies
    // NiceMock to suppress warnings about uninteresting mock calls
    std::shared_ptr<NiceMock<MockCardRepository>> cardRepoMock;
    std::shared_ptr<NiceMock<MockBanknoteService>> banknoteServiceMock;
    std::shared_ptr<NiceMock<MockTransactionRepository>> txRepoMock;

    // The service we are testing
    std::unique_ptr<CardService> service;

    // Test data
    Card debitCard;
    Card creditCard;
    std::string testCardNum = "1234567890123";
    std::string testPin = "1234";
    std::string testPinHash;

    void SetUp() override {
        // Create mocks
        cardRepoMock = std::make_shared<NiceMock<MockCardRepository>>();
        banknoteServiceMock = std::make_shared<NiceMock<MockBanknoteService>>();
        txRepoMock = std::make_shared<NiceMock<MockTransactionRepository>>();

        // Create the real service, injecting the mocks
        service = std::make_unique<CardService>(*cardRepoMock, *banknoteServiceMock, *txRepoMock);

        // Set up common test data
        testPinHash = BCrypt::generateHash(testPin);

        debitCard._cardNumber = testCardNum;
        debitCard._pin = testPinHash;
        debitCard._balance = 500;
        debitCard._creditLimit = 0;

        creditCard._cardNumber = "9876543210987";
        creditCard._pin = testPinHash;
        creditCard._balance = 0; // Balance on credit card is debt
        creditCard._creditLimit = 1000;
    }
};

// --- Authentication Tests ---

TEST_F(CardServiceTest, AuthSuccess) {
    // Arrange
    EXPECT_CALL(*cardRepoMock, doGetCard(testCardNum))
        .WillOnce(Return(debitCard));

    ASSERT_NO_THROW(service->authenticate(testCardNum, testPin));
}

TEST_F(CardServiceTest, AuthFailWrongPin) {
    // Arrange
    EXPECT_CALL(*cardRepoMock, doGetCard(testCardNum))
        .WillOnce(Return(debitCard));

    ASSERT_THROW(service->authenticate(testCardNum, "9999"), Exceptions);
}

TEST_F(CardServiceTest, AuthFailCardNotFound) {
    // Arrange
    // Configure the mock to throw RecordNotFound when this card is requested
    EXPECT_CALL(*cardRepoMock, doGetCard("000"))
        .WillOnce(Throw(Exceptions::RecordNotFound));

    ASSERT_THROW(service->authenticate("000", testPin), Exceptions);
}

// --- Withdrawal Tests ---

TEST_F(CardServiceTest, WithdrawDebitSuccess) {
    // Arrange
    debitCard._balance = 500;
    EXPECT_CALL(*cardRepoMock, doGetCard(testCardNum))
        .WillOnce(Return(debitCard));

    // Expect dispense to be called
    EXPECT_CALL(*banknoteServiceMock, doDispense(100)).Times(1);
    // Expect balance to be subtracted
    EXPECT_CALL(*cardRepoMock, doSubtractBalance(testCardNum, 100)).Times(1);
    // Expect a successful transaction to be logged
    EXPECT_CALL(*txRepoMock, doCreateTransaction(
        ::testing::AllOf(
            ::testing::Field(&Transaction::_amount, 100),
            ::testing::Field(&Transaction::_transactionStatus, TransactionStatus::SUCCESSFUL)
        )
    )).Times(1);

    ASSERT_NO_THROW(service->withdraw(testCardNum, 100));
}

TEST_F(CardServiceTest, WithdrawDebitFailInsufficientFunds) {
    // Arrange
    debitCard._balance = 50; // Not enough money
    EXPECT_CALL(*cardRepoMock, doGetCard(testCardNum))
        .WillOnce(Return(debitCard));

    // Expect dispense and subtract NOT to be called
    EXPECT_CALL(*banknoteServiceMock, doDispense(_)).Times(0);
    EXPECT_CALL(*cardRepoMock, doSubtractBalance(_, _)).Times(0);
    // Expect a FAILED transaction
    EXPECT_CALL(*txRepoMock, doCreateTransaction(
        ::testing::Field(&Transaction::_transactionStatus, TransactionStatus::FAILED)
    )).Times(1);

    ASSERT_THROW(service->withdraw(testCardNum, 100), Exceptions);
}

TEST_F(CardServiceTest, WithdrawCreditSuccess) {
    // Arrange
    creditCard._balance = 200; // 200 debt
    creditCard._creditLimit = 1000;
    EXPECT_CALL(*cardRepoMock, doGetCard(creditCard._cardNumber))
        .WillOnce(Return(creditCard));

    // Expect dispense
    EXPECT_CALL(*banknoteServiceMock, doDispense(100)).Times(1);
    // Expect balance to be *added* (increasing debt)
    EXPECT_CALL(*cardRepoMock, doAddBalance(creditCard._cardNumber, 100)).Times(1);
    // Expect a successful transaction
    EXPECT_CALL(*txRepoMock, doCreateTransaction(
        ::testing::Field(&Transaction::_transactionStatus, TransactionStatus::SUCCESSFUL)
    )).Times(1);

    ASSERT_NO_THROW(service->withdraw(creditCard._cardNumber, 100));
}

TEST_F(CardServiceTest, WithdrawCreditFailOverLimit) {
    // Arrange
    creditCard._balance = 950; // 950 debt
    creditCard._creditLimit = 1000;
    EXPECT_CALL(*cardRepoMock, doGetCard(creditCard._cardNumber))
        .WillOnce(Return(creditCard));

    // Expect nothing to be dispensed or charged
    EXPECT_CALL(*banknoteServiceMock, doDispense(_)).Times(0);
    EXPECT_CALL(*cardRepoMock, doAddBalance(_, _)).Times(0);
    // Expect a FAILED transaction
    EXPECT_CALL(*txRepoMock, doCreateTransaction(
        ::testing::Field(&Transaction::_transactionStatus, TransactionStatus::FAILED)
    )).Times(1);

    // Withdrawing 100 would put debt at 1050, which is > 1000 limit
    ASSERT_THROW(service->withdraw(creditCard._cardNumber, 100), Exceptions);
}

// --- Transfer Tests ---

TEST_F(CardServiceTest, TransferFailSameCard) {
    // Arrange
    // No repo calls should be needed

    // Expect a FAILED transaction
    EXPECT_CALL(*txRepoMock, doCreateTransaction(
        ::testing::AllOf(
            ::testing::Field(&Transaction::_fromCardNumber, testCardNum),
            ::testing::Field(&Transaction::_toCardNumber, testCardNum),
            ::testing::Field(&Transaction::_transactionStatus, TransactionStatus::FAILED)
        )
    )).Times(1);

    ASSERT_THROW(service->transfer(testCardNum, testCardNum, 100), Exceptions);
}

// --- Change PIN Tests ---

TEST_F(CardServiceTest, ChangePinSuccess) {
    // Arrange
    std::string newPin = "5678";
    EXPECT_CALL(*cardRepoMock, doGetCard(testCardNum))
        .WillOnce(Return(debitCard));
    // Expect updatePin to be called. We can't know the hash, so we just check it's not empty.
    EXPECT_CALL(*cardRepoMock, doUpdatePin(testCardNum, ::testing::Not(::testing::IsEmpty()))).Times(1);

    ASSERT_NO_THROW(service->changePin(testCardNum, newPin));
}

TEST_F(CardServiceTest, ChangePinFailSamePin) {
    // Arrange
    std::string samePin = "1234";
    EXPECT_CALL(*cardRepoMock, doGetCard(testCardNum))
        .WillOnce(Return(debitCard));
    // Expect updatePin NOT to be called
    EXPECT_CALL(*cardRepoMock, doUpdatePin(_, _)).Times(0);

    ASSERT_THROW(service->changePin(testCardNum, samePin), Exceptions);
}