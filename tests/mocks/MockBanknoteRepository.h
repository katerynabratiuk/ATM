#pragma once

#include "backend/repositories/IBanknoteRepository.h"
#include "gmock/gmock.h"
#include <vector>
#include <utility>

class MockBanknoteRepository : public IBanknoteRepository {
public:
    // Need to provide a dummy ATM ID to the parent constructor
    MockBanknoteRepository() : IBanknoteRepository(1) {}

    MOCK_METHOD(int, doGetCount, (Denominations denom), (override));
    MOCK_METHOD(void, doSetCount, (Denominations denom, int count), (override));
    MOCK_METHOD(std::vector<std::pair<Denominations, int>>, doGetAllCounts, (), (override));
};