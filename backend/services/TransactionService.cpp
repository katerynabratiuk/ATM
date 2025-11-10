#include "backend/services/TransactionService.h"
#include <stdexcept>

TransactionService::TransactionService(ITransactionRepository& repo)
    : _repo(repo)
{}

std::vector<Transaction> TransactionService::doListByCard(const std::string& cardNumber, 
    int limit, int offset)
{
    try
    {
        return _repo.listByCard(cardNumber, limit, offset);
    }
    catch (const std::exception& e)
    {
        throw;
	}
}

Transaction TransactionService::doGetLast(const std::string& cardNumber)
{
    try
    {
        return _repo.getLast(cardNumber);
    }
    catch (const std::exception& e)
    {
        throw;
    }
}