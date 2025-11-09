#include "backend/services/TransactionService.h"
#include <stdexcept>

TransactionService::TransactionService(ITransactionRepository& txRepository)
    : _txRepository(txRepository)
{
}

std::vector<Transaction> TransactionService::listByCard(const std::string& cardNumber, int limit, int offset)
{
    if (limit <= 0 || limit > 50)
    {
        limit = 10;
    }
    if (offset < 0)
    {
        offset = 0;
    }

    return _txRepository.listByCard(cardNumber, limit, offset);
}

Transaction TransactionService::getLast(const std::string& cardNumber)
{
    if (cardNumber.empty())
    {
        throw std::invalid_argument("Card number cannot be empty.");
    }
    return _txRepository.getLast(cardNumber);
}