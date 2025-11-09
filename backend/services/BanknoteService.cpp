#include "backend/services/BanknoteService.h"
#include <stdexcept>

// BanknoteService::BanknoteService(IBanknoteRepository& repo) : _repo(repo) {}

bool BanknoteService::canDispense(int amount)
{
    // TODO: Логіка, яка перевіряє _repo на наявність потрібних номіналів

    // Поки що, заглушка:
    if (amount > 10000)
    {
        return false;
    }
    return (amount % 100 == 0);
}

void BanknoteService::dispense(int amount)
{
    // TODO: Логіка оновлення кількості купюр в _repo

    if (!canDispense(amount))
    {
        throw std::runtime_error("Cannot dispense this amount.");
    }
    // ... логіка видачі
}