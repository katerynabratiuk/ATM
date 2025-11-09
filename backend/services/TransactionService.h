#pragma once

#include "backend/services/ITransactionService.h"
#include "backend/repositories/ITransactionRepository.h"

class TransactionService : public ITransactionService
{
public:
    TransactionService(ITransactionRepository& txRepository);

private:
    ITransactionRepository& _txRepository;

    std::vector<Transaction> listByCard(const std::string& cardNumber, int limit, int offset) override;
    Transaction getLast(const std::string& cardNumber) override;
};