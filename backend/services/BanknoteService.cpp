#include "backend/services/BanknoteService.h"

BanknoteService::BanknoteService(IBanknoteRepository& repo) : _repo(repo) {}

void BanknoteService::doDispense(int amount)
{
    return;
}
