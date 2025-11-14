#include "backend/services/CardService.h"
#include "backend/enums/Exceptions.h"
#include "backend/models/Card.h"
#include "backend/external/libbcrypt/include/bcrypt/BCrypt.hpp"

CardService::CardService(ICardRepository& cardRepository, IBanknoteService& banknoteService, ITransactionRepository& txRepo)
	: _repo(cardRepository), _banknoteService(banknoteService), _txRepo(txRepo)
{}

void CardService::doAuth(const std::string& cardNum, const std::string& pin)
{
    try {
        Card card = _repo.getCard(cardNum);

        if (!BCrypt::validatePassword(pin, card._pin))
        {
            throw Exceptions::AccessDenied;
        }
    }
    catch (const Exceptions& exception) {
        if (exception == Exceptions::DoesntExist) {
            throw; // Already the right exception
        }
        throw; // Let DBException/ConnectionError propagate
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
    catch (const Exceptions& exception)
    {
        _txRepo.addTransaction(Transaction(cardNum, cardNum,
            TransactionType::DEPOSIT, amount, TransactionStatus::FAILED));
        throw; // Re-throw all exceptions
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
    catch (const Exceptions& exception)
    {
        _txRepo.addTransaction(Transaction(cardNum, cardNum,
            TransactionType::WITHDRAWAL, amount, TransactionStatus::FAILED));
        throw; // Re-throw all exceptions
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
    catch (const Exceptions& exception)
    {
        _txRepo.addTransaction(Transaction(from, to,
            TransactionType::TRANSFER, amount, TransactionStatus::FAILED));
        throw; // Re-throw all exceptions
    }
}

void CardService::doChangePin(const std::string& cardNum, const std::string& newPin)
{
    try {
        Card card = _repo.getCard(cardNum);
        if (BCrypt::validatePassword(newPin, card._pin))
        {
            throw Exceptions::SamePassword;
        }
        std::string newHashedPass = BCrypt::generateHash(newPin);
        _repo.updatePin(cardNum, newHashedPass);
    }
    catch (const Exceptions& exception) {
        if (exception == Exceptions::DoesntExist) {
            throw;
        }
        throw; // Let DBException propagate
    }
}

Card CardService::doGetCard(const std::string& cardNum)
{
    try {
        return _repo.getCard(cardNum);
    }
    catch (const Exceptions& exception) {
        if (exception == Exceptions::DoesntExist) {
            throw;
        }
        throw; // Let DBException propagate
    }
}