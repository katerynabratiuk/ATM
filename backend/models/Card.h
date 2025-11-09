#pragma once
#include <string>
#include "backend/core/Money.h"

struct Card
{
	std::string _cardNumber;
	std::string _firstName;
	std::string _lastName;
	std::string _pin;
	atm::money::Money _balance;
	atm::money::Money _creditLimit;
};
