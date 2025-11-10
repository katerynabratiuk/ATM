#pragma once

#include "backend/services/IBanknoteService.h"
#include "backend/repositories/IBanknoteRepository.h"
#include <vector>

class BanknoteService : public IBanknoteService
{
public:
    BanknoteService(IBanknoteRepository& repo);

private:
    IBanknoteRepository& _repo;

    void doDispense(int amount) override;

    bool findComb(int target, const std::vector<std::pair<Denominations, int>>& notes,
        std::vector<std::pair<Denominations, int>>& res);
};