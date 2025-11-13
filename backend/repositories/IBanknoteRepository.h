#pragma once
#include <vector>
#include "backend/enums/Denominations.h"

class IBanknoteRepository
{
public:
    virtual ~IBanknoteRepository() = default;

  int getCount(Denominations denom) { return doGetCount(denom); }
  void setCount(Denominations denom, int count) { doSetCount(denom, count); }
  std::vector<std::pair<Denominations, int>> getAllCounts() { return doGetAllCounts(); }

protected:
    explicit IBanknoteRepository(long atmId)
        : _atmId(atmId) {
    }

    const long _atmId;

private:
	virtual int doGetCount(Denominations denom) = 0;
	virtual void doSetCount(Denominations denom, int count) = 0;
	virtual std::vector<std::pair<Denominations, int>> doGetAllCounts() = 0;
};
