#pragma once
#include <string>
#include "backend/models/Card.h"
#include "backend/core/Money.h"

class ICardRepository
{
public:
	void authenticate(const std::string& cardNumber, const std::string& pin)
	{
		doAuth(cardNumber, pin);
	}

	void deposit(const std::string& cardNumber, atm::money::Money amount)
	{
		doDeposit(cardNumber, amount);
	}

	void withdraw(const std::string& cardNumber, atm::money::Money amount)
	{
		doWithdraw(cardNumber, amount);
	}

	void transfer(const std::string& initiatorCardNumber,
		const std::string& targetCardNumber,
		atm::money::Money amount)
	{
		doTransfer(initiatorCardNumber, targetCardNumber, amount);
	}

	void changePin(const std::string& cardNumber, const std::string& newPin)
	{
		doChangePin(cardNumber, newPin);
	}

	Card getCard(const std::string& cardNumber)
	{
		return doGetCard(cardNumber);
	}
	~ICardRepository() = default;
private:
	virtual void doDeposit(const std::string& cardNumber, atm::money::Money amount) = 0;
	virtual void doWithdraw(const std::string& cardNumber, atm::money::Money amount) = 0;
	virtual void doTransfer(const std::string& initiatorCardNumber,
		const std::string& targetCardNumber,
		atm::money::Money amount) = 0;
	virtual void doChangePin(const std::string& cardNumber, const std::string& newPin) = 0;
	virtual Card doGetCard(const std::string& cardNumber) = 0;
};

