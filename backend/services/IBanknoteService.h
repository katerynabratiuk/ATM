#pragma once

class IBanknoteService
{
public:
    virtual ~IBanknoteService() = default;

    void dispense(int amount)
    {
		doDispense(amount);
    }
private:
	virtual void doDispense(int amount) = 0;
};