#pragma once
#include <unordered_map>
#include "backend/Denominations.h"

class IBanknoteRepository
{
public:
	virtual ~IBanknoteRepository() = default;

	void getCount(Denominations denom)
	{
		return doGetCount(denom);
	}

	void setCount(Denominations denom, int count)
	{
		return doSetCount(denom, count);
	}

	std::unordered_map<Denominations, int> getAllCounts()
	{
		return doGetAllCounts();
	}
private:
	virtual void doGetCount(Denominations denom) = 0;
	virtual void doSetCount(Denominations denom, int count) = 0;
	virtual std::unordered_map<Denominations, int> doGetAllCounts() = 0;
};
