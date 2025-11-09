#pragma once
#include <string>
#include "backend/controllers/ICardController.h"
#include "backend/services/ICardService.h"
#include "backend/models/Card.h"

struct Session
{
	const std::string _cardNum;
};

class CardController : public ICardController
{
	void doSetCard(const std::string& cardNum) override;
	virtual void doAuth(const std::string& pin) override;
	void doDeauth() override;
	void doDeposit(int amount) override;
	void doWithdraw(int amount) override;
	void doTransfer(const std::string& targetCardNum, int amount) override;
	void doChangePin(const std::string& newPin) override;
	Card doGetCard() override;
public:
	CardController(ICardService& service);
	~CardController();

	int _attempts;
	Session* _session;
	ICardService& _service;
};

