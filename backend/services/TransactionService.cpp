#include "backend/services/TransactionService.h"
#include "backend/enums/Exceptions.h"
#include <stdexcept>

TransactionService::TransactionService(ITransactionRepository& repo)
    : _repo(repo)
{}

std::vector<Transaction> TransactionService::doListByCard(const std::string& cardNumber)
{
    try {
        return _repo.listTransactions(cardNumber);
    }
    catch (const Exceptions& exception) {
        if (exception == Exceptions::DoesntExist) {
            return std::vector<Transaction>();
        }
        throw;
    }
}

Transaction TransactionService::doGetLast(const std::string& cardNumber)
{
    try {
        return _repo.getLastTransaction(cardNumber);
    }
    catch (const Exceptions& e) {
        std::cerr << "Error getting last transaction for card " << cardNumber << std::endl;
        throw;
    }
}