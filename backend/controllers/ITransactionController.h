#pragma once
#include <string>
#include <vector>
#include "backend/models/Transaction.h"

class ITransactionController
{
public:
    virtual ~ITransactionController() = default;

    std::vector<Transaction> getHistory(const std::string& cardNumber)
    {
		return doGetHistory(cardNumber);
    }

private:
    virtual std::vector<Transaction> doGetHistory(const std::string& cardNumber) = 0;
};
