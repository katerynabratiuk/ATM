#include "backend/controllers/TransactionController.h"

TransactionController::TransactionController(ITransactionService& service)
    : _service(service)
{}

std::vector<Transaction> TransactionController::doGetHistory(const std::string& cardNumber, 
    int limit, int offset)
{
    //if (limit <= 0) limit = 10;
    //if (offset < 0) offset = 0;

    try
    {
        return _service.listByCard(cardNumber, limit, offset);
    }
    catch (const std::exception& e)
    {
        throw;
	} 
}