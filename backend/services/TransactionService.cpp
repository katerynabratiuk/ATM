#include "backend/services/TransactionService.h"
#include "backend/enums/Exceptions.h"
#include <stdexcept>

TransactionService::TransactionService(ITransactionRepository& repo)
    : _repo(repo)
{}

std::vector<Transaction> TransactionService::doListByCard(const std::string& cardNumber, 
    int limit, int offset)
{
    try {
        return _repo.listTransactions(cardNumber);
    }
    catch (const DBExceptions& dbException) {
        if (dbException == DBExceptions::RecordNotFound) {
            return std::vector<Transaction>();
        }
        throw Exceptions::DoesntExist;
    }
}

Transaction TransactionService::doGetLast(const std::string& cardNumber)
{
    try {
        return _repo.getLastTransaction(cardNumber);
    }
    catch (const DBExceptions& dbException) {
        if (dbException == DBExceptions::RecordNotFound) {
            throw Exceptions::DoesntExist;
        }
        throw Exceptions::DoesntExist;
    }
}