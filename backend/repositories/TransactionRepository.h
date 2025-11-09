#pragma once
#include "backend/repositories/ITransactionRepository.h"
#include "backend/repositories/IDBConnection.h"
#include <pqxx/pqxx>

class TransactionRepository : public ITransactionRepository {
public:
	explicit TransactionRepository(IDBConnection<pqxx::connection>& db)
		: _connection(db) {
	}

private:
	IDBConnection<pqxx::connection>& _connection;

	void doCreateTransaction(Transaction transaction);
	std::vector<Transaction> doListTransactions(const std::string& cardNumber);
	Transaction doGetLastTransaction(const std::string& cardNumber);
};