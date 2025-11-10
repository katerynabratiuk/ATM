#include "backend/services/BanknoteService.h"
#include <unordered_map>

BanknoteService::BanknoteService(IBanknoteRepository& repo) : _repo(repo) {}

void BanknoteService::doDispense(int amount)
{
	try
	{
		std::vector<std::pair<Denominations, int>> counts = _repo.getAllCounts();
	}
	catch (const std::exception& e)
	{
		throw;
	}
}
