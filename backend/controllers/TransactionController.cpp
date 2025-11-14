#include "backend/controllers/TransactionController.h"

TransactionController::TransactionController(ITransactionService& service)
    : _service(service)
{}

std::vector<Transaction> TransactionController::doGetHistory(const std::string& cardNumber)
{
    return _service.listByCard(cardNumber);
}