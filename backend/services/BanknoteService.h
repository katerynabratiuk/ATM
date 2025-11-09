#pragma once

#include "backend/services/IBanknoteService.h"
#include "backend/repositories/IBanknoteRepository.h"

class BanknoteService : public IBanknoteService
{
public:
    BanknoteService(IBanknoteRepository& repo);

private:
    IBanknoteRepository& _repo;

    void doDispense(int amount) override;
};