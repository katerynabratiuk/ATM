#pragma once // Замість #include "backend/services/ICardService.h"

#include "backend/services/ICardService.h"
#include "backend/repositories/ICardRepository.h"
#include "backend/repositories/ITransactionRepository.h"
#include "backend/services/IBanknoteService.h"
class CardService : public ICardService
{
public:
    CardService(ICardRepository& cardRepository,
        ITransactionRepository& txRepository,
        IBanknoteService& banknoteService);

private:
    ICardRepository& _cardRepository;
    ITransactionRepository& _txRepository;
    IBanknoteService& _banknoteService;

    void doAuth(const std::string& cardNum, const std::string& pin) override;
    void doDeposit(const std::string& cardNum, int amount) override;
    void doWithdraw(const std::string& cardNum, int amount) override;
    void doTransfer(const std::string& from, const std::string& to, int amount) override;
    void doChangePin(const std::string& cardNum, const std::string& newPin) override;
    Card doGetCard(const std::string& cardNum) override;
};