#pragma once

#include "backend/controllers/ITransactionController.h"
#include "backend/services/ITransactionService.h"
#include "backend/models/Transaction.h"
#include <vector>
#include <string>

class TransactionController : public ITransactionController
{
public:
    TransactionController(ITransactionService& service);
private:
    ITransactionService& _service;

    std::vector<Transaction> doGetHistory(const std::string& cardNumber) override;
};