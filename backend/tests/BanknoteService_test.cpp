#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "backend/services/BanknoteService.h"
#include "backend/enums/Exceptions.h"
#include "mocks.h" // Our new mock header

// Use convenience aliases
using ::testing::_;
using ::testing::Return;
using ::testing::Throw;

class BanknoteServiceTest : public ::testing::Test {
protected:
    // We use a real BanknoteService but a mock repository
    std::shared_ptr<MockBanknoteRepository> repoMock;
    std::unique_ptr<BanknoteService> service;

    void SetUp() override {
        // Create the mock repository and the service under test
        repoMock = std::make_shared<MockBanknoteRepository>();
        service = std::make_unique<BanknoteService>(*repoMock);
    }

    void TearDown() override {
        // No manual cleanup needed thanks to smart pointers
    }
};

TEST_F(BanknoteServiceTest, DispenseSuccess) {
    // Arrange
    // Define the ATM's inventory
    std::vector<std::pair<Denominations, int>> notes = {
        {Denominations::D10, 20},
        {Denominations::D100, 5}
    };

    // Set expectations:
    // When getAllCounts() is called, return our inventory
    EXPECT_CALL(*repoMock, doGetAllCounts()).WillOnce(Return(notes));
    // When getCount(D100) is called, return 5
    EXPECT_CALL(*repoMock, doGetCount(Denominations::D100)).WillOnce(Return(5));
    // Expect setCount to be called with the new, decremented count
    EXPECT_CALL(*repoMock, doSetCount(Denominations::D100, 4)).Times(1);

    // We expect the dispense(100) call to succeed without throwing
    ASSERT_NO_THROW(service->dispense(100));
}

TEST_F(BanknoteServiceTest, DispenseSuccessComplexAmount) {
    // Arrange
    std::vector<std::pair<Denominations, int>> notes = {
        {Denominations::D10, 20},
        {Denominations::D100, 5}
    };

    // We are asking for 120. The algorithm should choose 1x100 and 2x10.
    EXPECT_CALL(*repoMock, doGetAllCounts()).WillOnce(Return(notes));

    EXPECT_CALL(*repoMock, doGetCount(Denominations::D100)).WillOnce(Return(5));
    EXPECT_CALL(*repoMock, doSetCount(Denominations::D100, 4)).Times(1);

    EXPECT_CALL(*repoMock, doGetCount(Denominations::D10)).WillOnce(Return(20));
    EXPECT_CALL(*repoMock, doSetCount(Denominations::D10, 18)).Times(1);

    ASSERT_NO_THROW(service->dispense(120));
}

TEST_F(BanknoteServiceTest, DispenseFailNoCombination) {
    // Arrange
    std::vector<std::pair<Denominations, int>> notes = {
        {Denominations::D100, 5} // Only 100s available
    };

    // We can't make 15 from 100s
    EXPECT_CALL(*repoMock, doGetAllCounts()).WillOnce(Return(notes));
    // We expect no calls to get/set count because it fails before that
    EXPECT_CALL(*repoMock, doGetCount(_)).Times(0);
    EXPECT_CALL(*repoMock, doSetCount(_, _)).Times(0);

    // We expect it to throw Exceptions::NoSuchCash
    ASSERT_THROW(service->dispense(15), Exceptions);
}

TEST_F(BanknoteServiceTest, DispenseFailNotEnoughNotes) {
    // Arrange
    std::vector<std::pair<Denominations, int>> notes = {
        {Denominations::D100, 1} // Only one 100
    };

    // We can't make 200 from one 100
    EXPECT_CALL(*repoMock, doGetAllCounts()).WillOnce(Return(notes));
    EXPECT_CALL(*repoMock, doGetCount(_)).Times(0);
    EXPECT_CALL(*repoMock, doSetCount(_, _)).Times(0);

    ASSERT_THROW(service->dispense(200), Exceptions);
}