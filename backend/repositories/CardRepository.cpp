#include "backend/repositories/CardRepository.h"
#include <iostream>
#include <pqxx/pqxx>
#include <pqxx/zview.hxx>
#include <pqxx/params.hxx>

void CardRepository::doAuth(const std::string& cardNumber,
    const std::string& pinCode)
{
    auto& conn = _connection.getConnection();

    pqxx::read_transaction txn{ conn };

    static constexpr std::string_view query =
        "SELECT 1 "
        "FROM public.card "
        "WHERE card_number = $1 "
        "  AND pin_hash = crypt($2, pin_hash) ";

    pqxx::result r = txn.exec_params(query, cardNumber, pinCode);

    if (r.empty()) {
        throw std::runtime_error("Authentication failed: card not found or wrong PIN");
    }
}



void CardRepository::doDeposit(const std::string&, int amount) {
    return;
}

void CardRepository::doWithdraw(const std::string&, int amount) {
    return;
}

void CardRepository::doChangePin(const std::string&, const std::string&) {
    return;
}

Card CardRepository::doGetCard(const std::string&) {
    return Card{};
}
