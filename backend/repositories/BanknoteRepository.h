#pragma once
#include "backend/repositories/IBanknoteRepository.h"
#include "backend/repositories/IDBConnection.h"
#include <pqxx/pqxx>
#include <utility>

class BanknoteRepository : public IBanknoteRepository
{
public:
    BanknoteRepository(IDBConnection<pqxx::connection>& db, long atmId)
        : IBanknoteRepository(atmId),
        _connection(db) {
    }

private:
    IDBConnection<pqxx::connection>& _connection;

    int doGetCount(Denominations denom) override;
    void doSetCount(Denominations denom, int count) override;
    std::vector<std::pair<Denominations, int>> doGetAllCounts() override;
};
