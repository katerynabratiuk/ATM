#pragma once
#include <string>
#include "ICardController.h"
#include "ICardService.h"

struct Session
{
	const std::string _cardNum;
};

class CardController : public ICardController
{
	void doAuth(const std::string& cardNum, const std::string& pin) override;
	void doDeauth() override;
	void doDeposit(double amount) override;
	void doWithdraw(double amount) override;
	void doTransfer(const std::string& targetCardNum, double amount) override;
	void doChangePin(const std::string& newPin) override;
	Card doGetCard() override;
public:
	CardController(ICardService& service);
	~CardController();

	int _attempts;
	Session* _session;
	ICardService& _service;
};

