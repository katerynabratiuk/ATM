#include "backend/repositories/TransactionRepository.h"
#include "backend/enums/Exceptions.h"
#include <vector>
#include <iostream>


static Transaction extractTransaction(const pqxx::row& row)
{
    Transaction t;
    t._id = row["id"].as<int>();
    t._fromCardNumber = row["from_card"].as<std::string>();
    t._toCardNumber = row["to_card"].as<std::string>();
    t._transactionType = from_string_type(row["type"].as<std::string>());
    t._transactionStatus = from_string_status(row["status"].as<std::string>());
    t._time = row["created_at"].as<std::string>();
    t._amount = row["amount"].as<int>();
    return t;
}

void TransactionRepository::doCreateTransaction(Transaction transaction) {
    try {
        auto& conn = _connection.getConnection();

        pqxx::work txn{ conn };

        const char* query =
            "INSERT INTO public.transactions(from_card, to_card, type, amount, status) "
            "VALUES ($1,$2,$3,$4,$5);";

        txn.exec_params(query,
            transaction._fromCardNumber,
            transaction._toCardNumber,
            to_string(transaction._transactionType),
            transaction._amount,
            to_string(transaction._transactionStatus)
        );

        txn.commit();
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
};


std::vector<Transaction> TransactionRepository::doListTransactions(const std::string& cardNumber)
{
    try {
        auto& conn = _connection.getConnection();

        pqxx::read_transaction txn{ conn };

        const char* query =
            "SELECT * FROM transactions WHERE from_card = $1 OR to_card = $1;";

        pqxx::result result = txn.exec_params(query, cardNumber);

        std::vector<Transaction> transactions;
        for (auto const& row : result) 
        {
            transactions.push_back(extractTransaction(row));
        }

        return transactions;
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


Transaction TransactionRepository::doGetLastTransaction(const std::string& cardNumber)
{
    try {
        auto& conn = _connection.getConnection();

        pqxx::read_transaction txn{ conn };

        const char* query =
            "SELECT * FROM transactions WHERE from_card = $1 OR to_card = $1 FETCH FIRST 1 ROWS ONLY;";

        pqxx::result result = txn.exec_params(query, cardNumber);

        if (result.empty()) {
            throw DBExceptions::RecordNotFound;
        }

        return extractTransaction(result[0]);
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
