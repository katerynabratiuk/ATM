#pragma once
#include <string>
#include "backend/models/Card.h"

class ICardRepository
{
public:

	void addBalance(const std::string& cardNumber, int amount)
	{
		doAddBalance(cardNumber, amount);
	}

	void subtractBalance(const std::string& cardNumber, int amount)
	{
		doSubtractBalance(cardNumber, amount);
	}

	void updatePin(const std::string& cardNumber, const std::string& newHashedPin)
	{
		doUpdatePin(cardNumber, newHashedPin);
	}

	Card getCard(const std::string& cardNumber)
	{
		return doGetCard(cardNumber);
	}
	~ICardRepository() = default;
private:
	virtual void doAddBalance(const std::string& cardNumber, int amount) = 0;
	virtual void doSubtractBalance(const std::string& cardNumber, int amount) = 0;
	virtual void doUpdatePin(const std::string& cardNumber, const std::string& newHashedPin) = 0;
	virtual Card doGetCard(const std::string& cardNumber) = 0;
};

