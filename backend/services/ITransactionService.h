#pragma once

#include "backend/models/Transaction.h"
#include <vector>
#include <string>

class ITransactionService
{
public:
    virtual ~ITransactionService() = default;

    virtual std::vector<Transaction> listByCard(const std::string& cardNumber, int limit, int offset) = 0;
    virtual Transaction getLast(const std::string& cardNumber) = 0;
};