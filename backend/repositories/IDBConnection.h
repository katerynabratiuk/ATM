#pragma once
#include <string>
#include <memory>

template<typename DBConnection>
class IDBConnection {
public:
    IDBConnection(const std::string& dbname,
        const std::string& user,
        const std::string& host,
        int port,
        const std::string& password)
        : _dbname(dbname), _user(user), _host(host), _port(port), _password(password) {
    }

    virtual ~IDBConnection() = default;

    bool connect() {
        return doConnect();
    }

    DBConnection& getConnection() {
        return doGetConnection();
    }


protected:
    const std::string _dbname;
    const std::string _user;
    const std::string _host;
    const int _port;
    const std::string _password;

    std::unique_ptr<DBConnection> connection;

    virtual bool doConnect() = 0;
    virtual DBConnection& doGetConnection() = 0;
};
