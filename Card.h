#pragma once
#include <string>
#include "decimal.h"

struct Card
{
	std::string _cardNumber;
	std::string _firstName;
	std::string _lastName;
	std::string _pin;
	dec::decimal<2> _balance;
	dec::decimal<2> _creditLimit;
};
