#pragma once
#include <string>
#include "backend/models/Card.h"

class ICardController
{
public:
	virtual ~ICardController() = default;

	void setCard(const std::string& cardNum)
	{
		doSetCard(cardNum);
	}

	void authenticate(const std::string& pin)
	{
		doAuth(pin);
	}

	void deauthenticate()
	{
		doDeauth();
	}

	void deposit(int amount)
	{
		doDeposit(amount);
	}

	void withdraw(int amount)
	{
		doWithdraw(amount);
	}

	void transfer(const std::string& targetCardNum, int amount)
	{
		doTransfer(targetCardNum, amount);
	}

	void changePin(const std::string& newPin)
	{
		doChangePin(newPin);
	}

	Card getCard()
	{
		return doGetCard();
	}
private:
	virtual void doSetCard(const std::string& cardNum) = 0;
	virtual void doAuth(const std::string& pin) = 0;
	virtual void doDeauth() = 0;
	virtual void doDeposit(int amount) = 0;
	virtual void doWithdraw(int amount) = 0;
	virtual void doTransfer(const std::string& targetCardNum, int amount) = 0;
	virtual void doChangePin(const std::string& newPin) = 0;
	virtual Card doGetCard() = 0;
};