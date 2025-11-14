#pragma once

#include "backend/repositories/ITransactionRepository.h"
#include "gmock/gmock.h"
#include "backend/models/Transaction.h"
#include <vector>
#include <string>

class MockTransactionRepository : public ITransactionRepository {
public:
    MOCK_METHOD(void, doCreateTransaction, (Transaction transaction), (override));
    MOCK_METHOD(std::vector<Transaction>, doListTransactions, (const std::string& cardNumber), (override));
    MOCK_METHOD(Transaction, doGetLastTransaction, (const std::string& cardNumber), (override));
};