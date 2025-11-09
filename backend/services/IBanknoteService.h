#pragma once

class IBanknoteService
{
public:
    virtual ~IBanknoteService() = default;

    virtual bool canDispense(int amount) = 0;
    virtual void dispense(int amount) = 0;
};