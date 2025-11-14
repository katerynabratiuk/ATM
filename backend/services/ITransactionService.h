#pragma once

#include "backend/models/Transaction.h"
#include <vector>
#include <string>

class ITransactionService
{
public:
    virtual ~ITransactionService() = default;

    std::vector<Transaction> listByCard(const std::string& cardNumber)
    {
		return doListByCard(cardNumber);
    }

    Transaction getLast(const std::string& cardNumber)
    {
		return doGetLast(cardNumber);
    }
private:
    virtual std::vector<Transaction> doListByCard(const std::string& cardNumber) = 0;
    virtual Transaction doGetLast(const std::string& cardNumber) = 0;
};