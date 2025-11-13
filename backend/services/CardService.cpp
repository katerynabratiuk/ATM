#include "backend/services/CardService.h"
#include "backend/enums/Exceptions.h"
#include "backend/models/Card.h"
#include "backend/external/libbcrypt/include/bcrypt/BCrypt.hpp"

CardService::CardService(ICardRepository& cardRepository, IBanknoteService& banknoteService,
    ITransactionRepository& txRepo)
	: _repo(cardRepository), _banknoteService(banknoteService), _txRepo(txRepo)
{}

void CardService::doAuth(const std::string& cardNum, const std::string& pin)
{
    Card card = _repo.getCard(cardNum);

    if (!BCrypt::validatePassword(pin, card._pin))
    {
        throw Exceptions::AccessDenied;
    }
}

void CardService::doDeposit(const std::string& cardNum, int amount)
{
    try
    {
        _repo.deposit(cardNum, amount);
        _txRepo.addTransaction(Transaction(cardNum, cardNum, 
            TransactionType::DEPOSIT, amount, TransactionStatus::SUCCESSFUL));
    }
    catch (Exceptions e)
    {
        _txRepo.addTransaction(Transaction(cardNum, cardNum,
            TransactionType::DEPOSIT, amount, TransactionStatus::FAILED));
        throw e;
	}
}

void CardService::doWithdraw(const std::string& cardNum, int amount)
{
    try
    {
        Card card = _repo.getCard(cardNum);
        if (card._balance < amount)
        {
            throw Exceptions::NotEnoughMoney;
        }

        _banknoteService.dispense(amount);
        _repo.withdraw(cardNum, amount);
        _txRepo.addTransaction(Transaction(cardNum, cardNum,
            TransactionType::WITHDRAWAL, amount, TransactionStatus::SUCCESSFUL));
    }
    catch (Exceptions e)
    {
        _txRepo.addTransaction(Transaction(cardNum, cardNum,
            TransactionType::WITHDRAWAL, amount, TransactionStatus::FAILED));
        throw e;
    }
}

void CardService::doTransfer(const std::string& from, const std::string& to, int amount)
{
    try
    {
        Card card = _repo.getCard(from);
        if (from == to)
        {
            throw Exceptions::SameCard;
		}
        if (card._balance < amount)
        {
            throw Exceptions::NotEnoughMoney;
		}

        _repo.withdraw(from, amount);
		_repo.deposit(to, amount);
        _txRepo.addTransaction(Transaction(from, to,
            TransactionType::WITHDRAWAL, amount, TransactionStatus::SUCCESSFUL));
    }
    catch (Exceptions e)
    {
        _txRepo.addTransaction(Transaction(from, to,
            TransactionType::WITHDRAWAL, amount, TransactionStatus::FAILED));
        throw e;
    }
}

void CardService::doChangePin(const std::string& cardNum, const std::string& newPin)
{
    Card card = _repo.getCard(cardNum);
    if (newPin == card._pin)
    {
        throw Exceptions::SamePassword;
    }
    _repo.changePin(cardNum, newPin);
}

Card CardService::doGetCard(const std::string& cardNum)
{
    return _repo.getCard(cardNum);
}