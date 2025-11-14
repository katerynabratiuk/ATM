#include "backend/services/TransactionService.h"
#include <stdexcept>

TransactionService::TransactionService(ITransactionRepository& repo)
    : _repo(repo)
{}

std::vector<Transaction> TransactionService::doListByCard(const std::string& cardNumber)
{
    return _repo.listTransactions(cardNumber);
}

Transaction TransactionService::doGetLast(const std::string& cardNumber)
{
    return _repo.getLastTransaction(cardNumber);
}