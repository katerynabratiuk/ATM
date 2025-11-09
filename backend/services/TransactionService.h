#pragma once

#include "backend/services/ITransactionService.h"
#include "backend/repositories/ITransactionRepository.h"

class TransactionService : public ITransactionService
{
public:
    TransactionService(ITransactionRepository& txRepository);

private:
    ITransactionRepository& _repo;

    std::vector<Transaction> doListByCard(const std::string& cardNumber, 
        int limit, int offset) override;
    Transaction doGetLast(const std::string& cardNumber) override;
};