#pragma once

#include "backend/models/Transaction.h"
#include <vector>
#include <string>

class ITransactionRepository
{
public:
    virtual ~ITransactionRepository() = default;

    virtual std::vector<Transaction> listByCard(const std::string& cardNumber, int limit, int offset) = 0;
    virtual Transaction getLast(const std::string& cardNumber) = 0;
    virtual void save(const Transaction& tx) = 0;
};