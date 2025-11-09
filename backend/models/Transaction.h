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
	long id;
	std::string fromCardNumber;
	std::string toCardNumber;
	std::chrono::time_point<std::chrono::system_clock> time;
	TransactionType transactionType;
	atm::money::Money amount;
	TransactionStatus transactionStatus;
};
