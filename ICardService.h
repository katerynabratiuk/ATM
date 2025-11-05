#pragma once
#include <string>
#include "Models.h"

class ICardService
{
public:
	void authenticate(const std::string& cardNum, const std::string& pin)
	{
		doAuth(cardNum, pin);
	}

	void deposit(const std::string& cardNum, double amount)
	{
		doDeposit(cardNum, amount);
	}

	void withdraw(const std::string& cardNum, double amount)
	{
		doWithdraw(cardNum, amount);
	}

	void transfer(const std::string& from, const std::string& to, double amount)
	{
		doTransfer(from, to, amount);
	}

	void changePin(const std::string& cardNum, const std::string& newPin)
	{
		changePin(cardNum, newPin);
	}

	Card getCard(const std::string& cardNum)
	{
		return doGetCard(cardNum);
	}
private:
	virtual void doAuth(const std::string& cardNum, const std::string& pin) = 0;
	virtual void doDeposit(const std::string& cardNum, double amount) = 0;
	virtual void doWithdraw(const std::string& cardNum, double amount) = 0;
	virtual void doTransfer(const std::string& from, const std::string& to, double amount) = 0;
	virtual void doChangePin(const std::string& cardNum, const std::string& newPin) = 0;
	virtual Card doGetCard(const std::string& cardNum) = 0;
};