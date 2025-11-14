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

    void doAddBalance(const std::string& cardNumber, int amount) override;
    void doSubtractBalance(const std::string& cardNumber, int amount) override;
    void doUpdatePin(const std::string& cardNumber, const std::string& newPin) override;
    Card doGetCard(const std::string& cardNumber) override;
};
