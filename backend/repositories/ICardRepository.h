#pragma once
#include <string>
#include "backend/models/Card.h"

class ICardRepository
{
public:

	void deposit(const std::string& cardNumber, int amount)
	{
		doDeposit(cardNumber, amount);
	}

	void withdraw(const std::string& cardNumber, int amount)
	{
		doWithdraw(cardNumber, amount);
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
	virtual void doDeposit(const std::string& cardNumber, int amount) = 0;
	virtual void doWithdraw(const std::string& cardNumber, int amount) = 0;
	virtual void doChangePin(const std::string& cardNumber, const std::string& newPin) = 0;
	virtual Card doGetCard(const std::string& cardNumber) = 0;
};

