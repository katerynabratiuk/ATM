#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <pqxx/pqxx>
#include "IDBConnection.h"

class PostgresDBConnection : public IDBConnection<pqxx::connection> {
public:
    PostgresDBConnection(const std::string& dbname,
        const std::string& user,
        const std::string& host,
        int port,
        const std::string& password)
        : IDBConnection(dbname, user, host, port, password)
    {
    }


protected:
    bool doConnect() override {
        try {
            std::string connStr = "postgresql://" + _user + ":" + _password + "@" + _host + ":" +
                std::to_string(_port) + "/" + _dbname +
                "?connect_timeout=5&sslmode=disable";

            conn = std::make_unique<pqxx::connection>(connStr);
            if (!conn->is_open()) {
                throw std::runtime_error("DB: failed to open connection");
            }

#ifndef NDEBUG
            std::cout << "DB connected: "
                << conn->username() << "@" << conn->hostname()
                << ":" << conn->port() << "\n";
#endif
            return true;
        }
        catch (const std::exception& e) {
            std::cerr << "DB connection failed: " << e.what() << "\n";
            return false;
        }
    }

    pqxx::connection& doGetConnection() override {
        if (!conn || !conn->is_open())
            throw std::runtime_error("Connection unsuccessful");
        return *conn;
    }

private:
    std::unique_ptr<pqxx::connection> conn;
};
