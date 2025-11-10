#include "backend/services/CardService.h"

CardService::CardService(ICardRepository& cardRepository, IBanknoteService& banknoteService,
    ITransactionRepository& txRepo)
	: _repo(cardRepository), _banknoteService(banknoteService), _txRepo(txRepo)
{}

void CardService::doAuth(const std::string& cardNum, const std::string& pin)
{
    try
    {
		Card card = _repo.getCard(cardNum);
        if (pin != card._pin)
        {
            throw;
		}
    }
    catch (const std::exception& e)
    {
        throw;
	}
}

void CardService::doDeposit(const std::string& cardNum, int amount)
{
    try
    {
        _repo.deposit(cardNum, amount);
        //_txRepo.addTransaction(cardNum, "", amount, TransactionType::DEPOSIT, TransactionStatus::SUCCESSFUL);
    }
    catch (const std::exception& e)
    {
        //_txRepo.addTransaction(cardNum, "", amount, TransactionType::DEPOSIT, TransactionStatus::FAILED);
        throw;
	}
}

void CardService::doWithdraw(const std::string& cardNum, int amount)
{
    try
    {   
        _banknoteService.dispense(amount);
        _repo.withdraw(cardNum, amount);
        //_txRepo.addTransaction(cardNum, "", amount, TransactionType::WITHDRAWAL, TransactionStatus::SUCCESSFUL);
    }
    catch (const std::exception& e)
    {
        //_txRepo.addTransaction(cardNum, "", amount, TransactionType::WITHDRAWAL, TransactionStatus::FAILED);
        throw;
    }
}

void CardService::doTransfer(const std::string& from, const std::string& to, int amount)
{
    try
    {
        _repo.withdraw(from, amount);
		_repo.deposit(to, amount);
        //_txRepo.addTransaction(from, to, amount, TransactionType::TRANSFER, TransactionStatus::SUCCESSFUL);
    }
    catch (const std::exception& e)
    {
        //_txRepo.addTransaction(from, to, amount, TransactionType::TRANSFER, TransactionStatus::FAILED);
        throw;
    }
}

void CardService::doChangePin(const std::string& cardNum, const std::string& newPin)
{
    try
    {
		_repo.changePin(cardNum, newPin);
    }
    catch (const std::exception& e)
    {
        throw;
    }
}

Card CardService::doGetCard(const std::string& cardNum)
{
    try
    {
        return _repo.getCard(cardNum);
    }
    catch (const std::exception& e)
    {
        throw;
    }
}