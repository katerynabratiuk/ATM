#pragma once

#include "backend/services/ITransactionService.h"
#include "backend/models/Transaction.h"
#include <vector>
#include <string>

class TransactionController
{
public:
    TransactionController(ITransactionService& service);

    std::vector<Transaction> getHistory(const std::string& cardNumber, int limit, int offset);

private:
    ITransactionService& _service;
};