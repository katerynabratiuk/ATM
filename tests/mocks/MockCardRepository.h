#pragma once

#include "backend/repositories/ICardRepository.h"
#include "gmock/gmock.h"
#include "backend/models/Card.h"
#include <string>

class MockCardRepository : public ICardRepository {
public:
    MOCK_METHOD(void, doAddBalance, (const std::string& cardNumber, int amount), (override));
    MOCK_METHOD(void, doSubtractBalance, (const std::string& cardNumber, int amount), (override));
    MOCK_METHOD(void, doUpdatePin, (const std::string& cardNumber, const std::string& newPin), (override));
    MOCK_METHOD(Card, doGetCard, (const std::string& cardNumber), (override));
};