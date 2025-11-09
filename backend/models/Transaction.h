#pragma once
#include <string>
#include <chrono>
#include "backend/core/Money.h"

enum class TransactionType {
	DEPOSIT,
	WITHDRAWAL,
	TRANSFER
};

enum class TransactionStatus {
	SUCCESSFUL,
	FAILED,
};

struct Transaction
{
	long _id;
	std::string _from;
	std::string _to;
	std::chrono::time_point<std::chrono::system_clock> _time;
	TransactionType _type;
	atm::money::Money _amount;
	TransactionStatus _status;
};
