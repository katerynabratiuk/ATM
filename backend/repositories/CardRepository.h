#pragma once
#include "ICardRepository.h"
#include "backend/models/Card.h"
#include "IDBConnection.h"
#include "backend/core/Money.h"
#include <pqxx/pqxx>

class CardRepository : public ICardRepository {
public:
    explicit CardRepository(IDBConnection<pqxx::connection>& db)
        : _connection(db) {
    }

private:
    IDBConnection<pqxx::connection>& _connection;

    void doDeposit(const std::string& cardNumber, atm::money::Money amount) override;
    void doWithdraw(const std::string& cardNumber, atm::money::Money amount) override;
    void doTransfer(const std::string& initiatorCardNumber,
        const std::string& targetCardNumber,
        atm::money::Money amount) override;
    void doChangePin(const std::string& cardNumber, const std::string& newPin) override;
    Card doGetCard(const std::string& cardNumber) override;
};
