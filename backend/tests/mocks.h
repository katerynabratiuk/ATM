#pragma once

#include "gmock/gmock.h"
#include "backend/repositories/IBanknoteRepository.h"
#include "backend/repositories/ICardRepository.h"
#include "backend/repositories/ITransactionRepository.h"
#include "backend/services/IBanknoteService.h"
#include "backend/services/ICardService.h"

// --- Repository Mocks ---

class MockBanknoteRepository : public IBanknoteRepository {
public:
    // We must pass the atmId to the base class constructor
    MockBanknoteRepository() : IBanknoteRepository(1) {}

    MOCK_METHOD(int, doGetCount, (Denominations denom), (override));
    MOCK_METHOD(void, doSetCount, (Denominations denom, int count), (override));
    MOCK_METHOD(std::vector<std::pair<Denominations, int>>, doGetAllCounts, (), (override));
};

class MockCardRepository : public ICardRepository {
public:
    MOCK_METHOD(void, doAddBalance, (const std::string& cardNumber, int amount), (override));
    MOCK_METHOD(void, doSubtractBalance, (const std::string& cardNumber, int amount), (override));
    MOCK_METHOD(void, doUpdatePin, (const std::string& cardNumber, const std::string& newHashedPin), (override));
    MOCK_METHOD(Card, doGetCard, (const std::string& cardNumber), (override));
};

class MockTransactionRepository : public ITransactionRepository {
public:
    MOCK_METHOD(void, doCreateTransaction, (Transaction transaction), (override));
    MOCK_METHOD(std::vector<Transaction>, doListTransactions, (const std::string& cardNumber), (override));
    MOCK_METHOD(Transaction, doGetLastTransaction, (const std::string& cardNumber), (override));
};


// --- Service Mocks ---

class MockBanknoteService : public IBanknoteService {
public:
    MOCK_METHOD(void, doDispense, (int amount), (override));
};

class MockCardService : public ICardService {
public:
    MOCK_METHOD(void, doAuth, (const std::string& cardNum, const std::string& pin), (override));
    MOCK_METHOD(void, doDeposit, (const std::string& cardNum, int amount), (override));
    MOCK_METHOD(void, doWithdraw, (const std::string& cardNum, int amount), (override));
    MOCK_METHOD(void, doTransfer, (const std::string& from, const std::string& to, int amount), (override));
    MOCK_METHOD(void, doChangePin, (const std::string& cardNum, const std::string& newPin), (override));
    MOCK_METHOD(Card, doGetCard, (const std::string& cardNum), (override));
};