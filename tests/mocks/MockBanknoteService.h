#pragma once

#include "backend/services/IBanknoteService.h"
#include "gmock/gmock.h"

class MockBanknoteService : public IBanknoteService {
public:
    MOCK_METHOD(void, doDispense, (int amount), (override));
};