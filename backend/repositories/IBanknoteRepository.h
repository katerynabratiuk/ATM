#pragma once
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
private:
	virtual void doGetCount(Denominations denom) = 0;
	virtual void doSetCount(Denominations denom, int count) = 0;
};
