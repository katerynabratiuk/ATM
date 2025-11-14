#include "backend/repositories/BanknoteRepository.h"
#include "backend/enums/Exceptions.h"
#include <string_view>
#include <stdexcept>
#include <iostream>

int BanknoteRepository::doGetCount(Denominations denom)
{
    try {
        auto& conn = _connection.getConnection();
        pqxx::read_transaction txn{ conn };

        const std::string_view query =
            "SELECT count "
            "FROM banknote "
            "WHERE denominator = $1 AND atm_id = $2;";

        pqxx::result r = txn.exec_params(query, static_cast<int>(denom), _atmId);

        if (r.empty()) return 0;
        return r[0]["count"].as<int>();
    }
    catch (const pqxx::broken_connection& e) {
        std::cerr << "Connection error: " << e.what() << "\n"; 
    }
    catch (const pqxx::sql_error& e) {
        std::cerr << "Database error: " << e.what() << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << "\n";
    }
    throw Exceptions::DBException;
}

void BanknoteRepository::doSetCount(Denominations denom, int count)
{
    try {
        auto& conn = _connection.getConnection();
        pqxx::work txn{ conn };

        const std::string_view upsert =
            "INSERT INTO banknote (atm_id, denominator, count) "
            "VALUES ($1, $2, $3) "
            "ON CONFLICT (atm_id, denominator) "
            "DO UPDATE SET count = EXCLUDED.count;";

        txn.exec_params(upsert, _atmId, static_cast<int>(denom), count);
        txn.commit();
    }
    catch (const pqxx::broken_connection& e) {
        std::cerr << "Connection error: " << e.what() << "\n";
    }
    catch (const pqxx::sql_error& e) {
        std::cerr << "Database error: " << e.what() << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << "\n";
    }
    throw Exceptions::DBException;
}

std::vector<std::pair<Denominations, int>> BanknoteRepository::doGetAllCounts()
{
    try {
        auto& conn = _connection.getConnection();
        pqxx::read_transaction txn{ conn };

        const std::string_view query =
            "SELECT denominator, count "
            "FROM banknote "
            "WHERE atm_id = $1 "
            "ORDER BY denominator;";

        pqxx::result r = txn.exec_params(query, _atmId);

        std::vector<std::pair<Denominations, int>> counts;
        counts.reserve(r.size());

        for (const auto& row : r)
        {
            const int denomValue = row["denominator"].as<int>();
            const int cnt = row["count"].as<int>();
            counts.emplace_back(static_cast<Denominations>(denomValue), cnt);
        }
        return counts;
    }
    catch (const pqxx::broken_connection& e) {
        std::cerr << "Connection error: " << e.what() << "\n";
        throw Exceptions::DBException;
    }
    catch (const pqxx::sql_error& e) {
        std::cerr << "Database error: " << e.what() << "\n";
        throw Exceptions::DBException;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << "\n";
        throw Exceptions::DBException;
    }
}
