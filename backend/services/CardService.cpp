#include "backend/services/CardService.h"
#include "backend/enums/Exceptions.h"
#include "backend/models/Card.h"
#include "backend/external/libbcrypt/include/bcrypt/BCrypt.hpp"

CardService::CardService(ICardRepository& cardRepository, IBanknoteService& banknoteService, ITransactionRepository& txRepo)
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
        Card card = _repo.getCard(cardNum);
        if (card._creditLimit > 0) _repo.subtractBalance(cardNum, amount);
		else _repo.addBalance(cardNum, amount);
        
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
        if (card._creditLimit <= 0)
        {
            if (card._balance < amount)
            {
                throw Exceptions::NotEnoughMoney;
            }
            _banknoteService.dispense(amount);
			_repo.subtractBalance(cardNum, amount);
        }
        else
        {
            if (card._balance + amount > card._creditLimit)
            {
                throw Exceptions::NotEnoughMoney;
            }
            _banknoteService.dispense(amount);
			_repo.addBalance(cardNum, amount);
        }

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
        if (from == to)
        {
            throw Exceptions::SameCard;
		}

        Card cardTo = _repo.getCard(to);
        Card cardFrom = _repo.getCard(from);

        if (cardFrom._creditLimit <= 0)
        {
            if (cardFrom._balance < amount)
            {
                throw Exceptions::NotEnoughMoney;
            }
            _repo.subtractBalance(from, amount);
        }
        else
        {
            if (cardFrom._balance + amount > cardFrom._creditLimit)
            {
                throw Exceptions::NotEnoughMoney;
            }
            _repo.addBalance(from, amount);
        }

        if (cardTo._creditLimit > 0) _repo.subtractBalance(to, amount);
        else _repo.addBalance(to, amount);

        _txRepo.addTransaction(Transaction(from, to,
            TransactionType::TRANSFER, amount, TransactionStatus::SUCCESSFUL));
    }
    catch (Exceptions e)
    {
        _txRepo.addTransaction(Transaction(from, to,
            TransactionType::TRANSFER, amount, TransactionStatus::FAILED));
        throw e;
    }
}

void CardService::doChangePin(const std::string& cardNum, const std::string& newPin)
{
    Card card = _repo.getCard(cardNum);
    if (BCrypt::validatePassword(newPin, card._pin))
    {
        throw Exceptions::SamePassword;
    }
    std::string newHashedPass = BCrypt::generateHash(newPin);
    _repo.changePin(cardNum, newHashedPass);
}

Card CardService::doGetCard(const std::string& cardNum)
{
    return _repo.getCard(cardNum);
}