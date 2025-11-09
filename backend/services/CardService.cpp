#include "backend/services/CardService.h"
#include "backend/core/Money.h"
#include <stdexcept>
#include <regex>

static atm::money::Money toMoney(int amount)
{
    return atm::money::Money(amount);
}

CardService::CardService(ICardRepository& cardRepository,
    ITransactionRepository& txRepository,
    IBanknoteService& banknoteService)
    : _cardRepository(cardRepository),
    _txRepository(txRepository),
    _banknoteService(banknoteService)
{
}


static void validateAmount(int amountInt)
{
    if (amountInt <= 0)
    {
        throw std::invalid_argument("Amount must be positive.");
    }
}

void CardService::doAuth(const std::string& cardNum, const std::string& pin)
{
    if (!std::regex_match(pin, std::regex("^\\d{4}$")))
    {
        throw std::invalid_argument("PIN must be 4 digits.");
    }
    _cardRepository.authenticate(cardNum, pin);
}

void CardService::doDeposit(const std::string& cardNum, int amount)
{
    validateAmount(amount);

    _cardRepository.deposit(cardNum, toMoney(amount));

    Transaction tx;
    tx.fromCardNumber = cardNum;
    tx.toCardNumber = cardNum;
    tx.amount = toMoney(amount);
    tx.transactionType = TransactionType::DEPOSIT;
    tx.transactionStatus = TransactionStatus::SUCCESSFUL;
    // tx.time = ... (має встановлюватися автоматично)
    _txRepository.save(tx);
}

void CardService::doWithdraw(const std::string& cardNum, int amount)
{
    validateAmount(amount);

    if (amount % 100 != 0)
    {
        throw std::invalid_argument("Withdrawal amount must be a multiple of 100.");
    }

    Card card = _cardRepository.getCard(cardNum);
    if (toMoney(amount) > card._balance)
    {
        throw std::runtime_error("Insufficient funds.");
    }

    if (!_banknoteService.canDispense(amount))
    {
        throw std::runtime_error("Insufficient cash in ATM.");
    }

    _cardRepository.withdraw(cardNum, toMoney(amount));
    _banknoteService.dispense(amount);

    Transaction tx;
    tx.fromCardNumber = cardNum;
    tx.amount = toMoney(amount);
    tx.transactionType = TransactionType::WITHDRAWAL;
    tx.transactionStatus = TransactionStatus::SUCCESSFUL;
    _txRepository.save(tx);
}

void CardService::doTransfer(const std::string& from, const std::string& to, int amount)
{
    validateAmount(amount);

    if (from == to)
    {
        throw std::invalid_argument("Cannot transfer to the same card.");
    }

    Card fromCard = _cardRepository.getCard(from);
    if (toMoney(amount) > fromCard._balance)
    {
        throw std::runtime_error("Insufficient funds for transfer.");
    }

    try
    {
        _cardRepository.getCard(to);
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error("Recipient card not found.");
    }

    _cardRepository.transfer(to, toMoney(amount));

    Transaction tx;
    tx.fromCardNumber = from;
    tx.toCardNumber = to;
    tx.amount = toMoney(amount);
    tx.transactionType = TransactionType::TRANSFER;
    tx.transactionStatus = TransactionStatus::SUCCESSFUL;
    _txRepository.save(tx);
}

void CardService::doChangePin(const std::string& cardNum, const std::string& newPin)
{
    if (!std::regex_match(newPin, std::regex("^\\d{4}$")))
    {
        throw std::invalid_argument("PIN must be 4 digits.");
    }

    _cardRepository.changePin(cardNum, newPin);
}

Card CardService::doGetCard(const std::string& cardNum)
{
    return _cardRepository.getCard(cardNum);
}