#include "backend/controllers/CardController.h"
#include "backend/enums/Exceptions.h"

CardController::CardController(ICardService& service) : _session(nullptr), _service(service), _attempts(0)
{}

CardController::~CardController()
{
	doDeauth();
}

void CardController::doAuth(const std::string& pin)
{
	try 
	{
		if (_attempts >= 3)
		{
			doDeauth();
			throw Exceptions::TooManyAttempts;
		}
		_service.authenticate(_session->_cardNum, pin);
	}
	catch (Exceptions e)
	{
		_attempts++;
		throw e;
	}
}

void CardController::doSetCard(const std::string& cardNum)
{
	_service.getCard(cardNum);
	_session = new Session{ cardNum };
}

void CardController::doDeauth()
{
	_attempts = 0;
	delete _session;
	_session = nullptr;
}

void CardController::doDeposit(int amount)
{
	_service.deposit(_session->_cardNum, amount);
}

void CardController::doWithdraw(int amount)
{
	_service.withdraw(_session->_cardNum, amount);
}

void CardController::doTransfer(const std::string& targetCardNum, int amount)
{
	_service.transfer(_session->_cardNum, targetCardNum, amount);
}

void CardController::doChangePin(const std::string& newPin)
{
	_service.changePin(_session->_cardNum, newPin);
}

Card CardController::doGetCard()
{
	return _service.getCard(_session->_cardNum);
}
