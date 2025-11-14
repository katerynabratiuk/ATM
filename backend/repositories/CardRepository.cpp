#include "backend/repositories/CardRepository.h"
#include "backend/models/Card.h"
#include "backend/core/Money.h"
#include "backend/enums/Exceptions.h"
#include <iostream>
#include <pqxx/pqxx>
#include <pqxx/zview.hxx>
#include <pqxx/params.hxx>
#include <stdexcept>


void CardRepository::doAddBalance(const std::string& cardNumber, int amount) {
    try 
    {
    auto& conn = _connection.getConnection();
    

    pqxx::work txn{ conn };

    const std::string_view query =
        "UPDATE card "
        "SET balance = balance + $2 "
        "WHERE card_number = $1;";

    txn.exec_params(query, cardNumber, amount);
    txn.commit();
    return;
    }
    catch (const pqxx::broken_connection& e) {
        std::cerr << "Connection error: " << e.what() << "\n";
        throw DBExceptions::ConnectionError;
    }
    catch (const pqxx::sql_error& e) {
        std::cerr << "Database error: " << e.what() << "\n";
        throw DBExceptions::DatabaseError;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << "\n";
        throw DBExceptions::DatabaseError;
}

void CardRepository::doSubtractBalance(const std::string& cardNumber, int amount) {
    try 
    {
    auto& conn = _connection.getConnection();

    pqxx::work txn{ conn };

    const std::string_view query =
        "UPDATE card "
        "SET balance = balance - $2 "
        "WHERE card_number = $1;";

    txn.exec_params(query, cardNumber, amount);
    txn.commit();
    return;
    }
    catch (const pqxx::broken_connection& e) {
        std::cerr << "Connection error: " << e.what() << "\n";
        throw DBExceptions::ConnectionError;
    }
    catch (const pqxx::sql_error& e) {
        std::cerr << "Database error: " << e.what() << "\n";
        throw DBExceptions::DatabaseError;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << "\n";
        throw DBExceptions::DatabaseError;
}

void CardRepository::doUpdatePin(const std::string& cardNumber, const std::string& pin) {
    try 
    {
    auto& conn = _connection.getConnection();

    pqxx::work txn{ conn };

    const std::string_view query =
        "UPDATE card "
        "SET pin_hash = crypt($2, pin_hash) "
        "WHERE card_number = $1;";

    txn.exec_params(query, cardNumber, pin);
    txn.commit();
    return;
    }
    catch (const pqxx::broken_connection& e) {
        std::cerr << "Connection error: " << e.what() << "\n";
        throw DBExceptions::ConnectionError;
    }
    catch (const pqxx::sql_error& e) {
        std::cerr << "Database error: " << e.what() << "\n";
        throw DBExceptions::DatabaseError;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << "\n";
        throw DBExceptions::DatabaseError;
}

Card CardRepository::doGetCard(const std::string& cardNumber){
    try {
        auto& conn = _connection.getConnection();

        pqxx::read_transaction txn{ conn };

        const std::string_view query =
            "SELECT * "
            "FROM card "
            "WHERE card_number = $1";

        pqxx::result result = txn.exec_params(query, cardNumber);

        if (result.empty()) {
            throw DBExceptions::RecordNotFound;
        }

        auto row = result[0];

        Card card;
        card._cardNumber = row["card_number"].as<std::string>();;
        card._firstName = row["first_name"].as<std::string>();;
        card._lastName = row["last_name"].as<std::string>();;
        card._pin = row["pin_hash"].as<std::string>();;

        card._balance = atm::money::Money{ row["balance"].as<std::string>() };
        card._creditLimit = atm::money::Money{ row["credit_limit"].as<std::string>() };

        return card;
    }
    catch (const DBExceptions& dbException) {
        throw;
    }
    catch (const pqxx::broken_connection& e) {
        std::cerr << "Connection error: " << e.what() << "\n";
        throw DBExceptions::ConnectionError;
    }
    catch (const pqxx::sql_error& e) {
        std::cerr << "Database error: " << e.what() << "\n";
        throw DBExceptions::DatabaseError;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << "\n";
        throw DBExceptions::DatabaseError;
    }
}
