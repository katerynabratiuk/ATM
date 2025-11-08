#pragma once
#include "ICardRepository.h"
#include "Card.h"
#include "IDBConnection.h"
#include "decimal.h"
#include <pqxx/pqxx>


class CardRepository : public ICardRepository {

public:
	CardRepository(IDBConnection<pqxx::connection>& db) : _connection(db) {};

private:

	IDBConnection<pqxx::connection>& _connection;

	void doAuth(const std::string& cardNumber, const std::string& pin) override;
	void doDeposit(const std::string& cardNumber, dec::decimal<2> amount) override;
	void doWithdraw(const std::string& cardNumber, dec::decimal<2> amount) override;
	void doTransfer(const std::string& targetCardNumber, dec::decimal<2> amount) override;
	void doChangePin(const std::string& cardNumber, const std::string& newPin) override;
	Card doGetCard(const std::string& cardNumber) override;

};