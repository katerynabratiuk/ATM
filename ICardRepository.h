#pragma once

#include <string>
#include "Card.h"

class ICardRepository
{
public:
	void authenticate(const std::string& cardNumber, const std::string& pin)
	{
		doAuth(cardNumber, pin);
	}

	void deposit(const std::string& cardNumber, dec::decimal<2> amount)
	{
		doDeposit(cardNumber, amount);
	}

	void withdraw(const std::string& cardNumber, dec::decimal<2> amount)
	{
		doWithdraw(cardNumber, amount);
	}

	void transfer(const std::string& targetCardNumber, dec::decimal<2> amount)
	{
		doTransfer(targetCardNumber, amount);
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
	virtual void doAuth(const std::string& cardNumber, const std::string& pin) = 0;
	virtual void doDeposit(const std::string& cardNumber, dec::decimal<2> amount) = 0;
	virtual void doWithdraw(const std::string& cardNumber, dec::decimal<2> amount) = 0;
	virtual void doTransfer(const std::string& targetCardNumber, dec::decimal<2> amount) = 0;
	virtual void doChangePin(const std::string& cardNumber, const std::string& newPin) = 0;
	virtual Card doGetCard(const std::string& cardNumber) = 0;
};

