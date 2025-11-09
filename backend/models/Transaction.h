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
	std::string _fromCardNumber;
	std::string _toCardNumber;
	std::string _time;
	TransactionType _transactionType;
	atm::money::Money _amount;
	TransactionStatus _transactionStatus;
};


static std::string to_string(TransactionType t) {
    switch (t) {
    case TransactionType::DEPOSIT:  return "DEPOSIT";
    case TransactionType::WITHDRAWAL: return "WITHDRAWAL";
    case TransactionType::TRANSFER: return "TRANSFER";
    }
    return "UNKNOWN";
}

static std::string to_string(TransactionStatus s) {
    switch (s) {
    case TransactionStatus::SUCCESSFUL:  return "SUCCESSFUL";
    case TransactionStatus::FAILED:   return "FAILED";
    }
    return "UNKNOWN";
}

static TransactionType from_string_type(const std::string& t) {
    if (t == "DEPOSIT") {
        return TransactionType::DEPOSIT;
    }
    else if (t == "WITHDRAWAL") {
        return TransactionType::WITHDRAWAL;
    }
    else if (t == "TRANSFER") {
        return TransactionType::TRANSFER;
    }
    return TransactionType::DEPOSIT;
}

static TransactionStatus from_string_status(const std::string& s) {
    if (s == "SUCCESSFUL") {
        return TransactionStatus::SUCCESSFUL;
    }
    else if (s == "FAILED") {
        return TransactionStatus::FAILED;
    }
    return TransactionStatus::FAILED;
}
