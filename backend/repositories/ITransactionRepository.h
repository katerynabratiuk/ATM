#pragma once
#include "backend/models/Transaction.h"
#include <vector>

class ITransactionRepository {
public:
	void addTransaction(Transaction transaction) {
		return doCreateTransaction(transaction);
	}
	std::vector<Transaction> listTransactions(const std::string& cardNumber) {
		return doListTransactions(cardNumber);
	}
	Transaction getLastTransaction(const std::string& cardNumber) {
		return doGetLastTransaction(cardNumber);
	}

private:
	virtual void doCreateTransaction(Transaction transaction) = 0;
	virtual std::vector<Transaction> doListTransactions(const std::string& cardNumber) = 0;
	virtual Transaction doGetLastTransaction(const std::string& cardNumber) = 0;
	
};