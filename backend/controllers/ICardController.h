#pragma once
#include <string>
#include "backend/Models.h"

class ICardController
{
public:
	virtual ~ICardController() = default;

	void authenticate(const std::string& cardNum, const std::string& pin)
	{
		doAuth(cardNum, pin);
	}

	void deauthenticate()
	{
		doDeauth();
	}

	void deposit(double amount)
	{
		doDeposit(amount);
	}

	void withdraw(double amount)
	{
		doWithdraw(amount);
	}

	void transfer(const std::string& targetCardNum, double amount)
	{
		doTransfer(targetCardNum, amount);
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
	virtual void doAuth(const std::string& cardNum, const std::string& pin) = 0;
	virtual void doDeauth() = 0;
	virtual void doDeposit(double amount) = 0;
	virtual void doWithdraw(double amount) = 0;
	virtual void doTransfer(const std::string& targetCardNum, double amount) = 0;
	virtual void doChangePin(const std::string& newPin) = 0;
	virtual Card doGetCard() = 0;
};

