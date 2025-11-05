#pragma once
#include <string>
#include "Models.h"

class ICardController
{
public:
	void authenticate(const std::string& cardNumber, const std::string& pin)
	{
		doAuth(cardNumber, pin);
	}

	void deposit(double amount)
	{
		doDeposit(amount);
	}

	void withdraw(double amount)
	{
		doWithdraw(amount);
	}

	void transfer(const std::string& targetCardNumber, double amount)
	{
		doTransfer(targetCardNumber, amount);
	}

	void changePin(const std::string& newPin)
	{
		changePin(newPin);
	}

	Card getCard()
	{
		return doGetCard();
	}
private:
	virtual void doAuth(const std::string& cardNumber, const std::string& pin) = 0;
	virtual void doDeposit(double amount) = 0;
	virtual void doWithdraw(double amount) = 0;
	virtual void doTransfer(const std::string& targetCardNumber, double amount) = 0;
	virtual void doChangePin(const std::string& newPin) = 0;
	virtual Card doGetCard() = 0;
};

