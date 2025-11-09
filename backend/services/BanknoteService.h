#pragma once

#include "backend/services/IBanknoteService.h"
// #include "backend/repositories/IBanknoteRepository.h" // Потрібен буде репозиторій

class BanknoteService : public IBanknoteService
{
public:
    // BanknoteService(IBanknoteRepository& repo);

    bool canDispense(int amount) override;
    void dispense(int amount) override;

private:
    // IBanknoteRepository& _repo;

    // TODO: логіка підрахунку купюр
};