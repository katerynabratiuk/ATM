#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "backend/services/BanknoteService.h"
#include "backend/enums/Exceptions.h"
#include "backend/enums/Denominations.h"
#include "mocks/MockBanknoteRepository.h"
#include <vector>
#include <utility>

using ::testing::Return;
using ::testing::_;

class BanknoteServiceTest : public ::testing::Test {
protected:
    MockBanknoteRepository mockRepo;
    BanknoteService banknoteService;

    BanknoteServiceTest() : banknoteService(mockRepo) {}
};

TEST_F(BanknoteServiceTest, DispenseSuccess) {
    // Setup mock
    std::vector<std::pair<Denominations, int>> counts = {
        {Denominations::D10, 10},
        {Denominations::D20, 10},
        {Denominations::D50, 10},
        {Denominations::D100, 10}
    };
    EXPECT_CALL(mockRepo, getAllCounts())
        .WillOnce(Return(counts));

    // Expect the service to decrease the count of 100 and 50 banknotes
    EXPECT_CALL(mockRepo, getCount(Denominations::D100))
        .WillOnce(Return(10));
    EXPECT_CALL(mockRepo, setCount(Denominations::D100, 9)); // 10 - 1 = 9

    EXPECT_CALL(mockRepo, getCount(Denominations::D50))
        .WillOnce(Return(10));
    EXPECT_CALL(mockRepo, setCount(Denominations::D50, 9)); // 10 - 1 = 9

    // Call the method
    banknoteService.dispense(150); // 1*100 + 1*50
}

TEST_F(BanknoteServiceTest, DispenseFailureNoSuchCash) {
    // Setup mock: ATM only has 100 banknotes
    std::vector<std::pair<Denominations, int>> counts = {
        {Denominations::D100, 5}
    };
    EXPECT_CALL(mockRepo, getAllCounts())
        .WillOnce(Return(counts));

    // Attempt to withdraw 150, when it's impossible to dispense that amount
    EXPECT_THROW(banknoteService.dispense(150), Exceptions::NoSuchCash);
}

TEST_F(BanknoteServiceTest, DispenseFailureNotEnoughBanknotes) {
    // Setup mock: ATM has one 100 UAH banknote
    std::vector<std::pair<Denominations, int>> counts = {
        {Denominations::D100, 1}
    };
    EXPECT_CALL(mockRepo, getAllCounts())
        .WillOnce(Return(counts));

    // Attempt to withdraw 200
    EXPECT_THROW(banknoteService.dispense(200), Exceptions::NoSuchCash);
}

TEST_F(BanknoteServiceTest, DispenseComplexSuccess) {
    // Setup mock
    std::vector<std::pair<Denominations, int>> counts = {
        {Denominations::D10, 5},
        {Denominations::D20, 5},
        {Denominations::D50, 2},
        {Denominations::D100, 2}
    };
    EXPECT_CALL(mockRepo, getAllCounts())
        .WillOnce(Return(counts)); // Total 5*10 + 5*20 + 2*50 + 2*100 = 50 + 100 + 100 + 200 = 450

    // Expected calls for amount 330 = 2*100 + 2*50 + 1*20 + 1*10
    EXPECT_CALL(mockRepo, getCount(Denominations::D100))
        .WillOnce(Return(2));
    EXPECT_CALL(mockRepo, setCount(Denominations::D100, 0)); // 2 - 2 = 0

    EXPECT_CALL(mockRepo, getCount(Denominations::D50))
        .WillOnce(Return(2));
    EXPECT_CALL(mockRepo, setCount(Denominations::D50, 0)); // 2 - 2 = 0

    EXPECT_CALL(mockRepo, getCount(Denominations::D20))
        .WillOnce(Return(5));
    EXPECT_CALL(mockRepo, setCount(Denominations::D20, 4)); // 5 - 1 = 4

    EXPECT_CALL(mockRepo, getCount(Denominations::D10))
        .WillOnce(Return(5));
    EXPECT_CALL(mockRepo, setCount(Denominations::D10, 4)); // 5 - 1 = 4

    // Call the method
    banknoteService.dispense(330);
}