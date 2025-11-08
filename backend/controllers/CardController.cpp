#include "backend/controllers/CardController.h"

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

			// tooManyAttemptsException
			throw;
		}
		_service.authenticate(_session->_cardNum, pin);
	}
	catch (const std::exception& e)
	{
		_attempts++;
		throw;
	}
}

void CardController::doSetCard(const std::string& cardNum)
{
	try
	{
		_service.getCard(cardNum);
	}
	catch (const std::exception& e)
	{
		throw;
	}
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
	try
	{
		_service.deposit(_session->_cardNum, amount);
	}
	catch (const std::exception& e)
	{
		throw;
	}
}

void CardController::doWithdraw(int amount)
{
	try
	{
		_service.withdraw(_session->_cardNum, amount);
	}
	catch (const std::exception& e)
	{
		throw;
	}
}

void CardController::doTransfer(const std::string& targetCardNum, int amount)
{
	try
	{
		_service.transfer(_session->_cardNum, targetCardNum, amount);
	}
	catch (const std::exception& e)
	{
		throw;
	}
}

void CardController::doChangePin(const std::string& newPin)
{
	try
	{
		_service.changePin(_session->_cardNum, newPin);
	}
	catch (const std::exception& e)
	{
		throw;
	}
}

Card CardController::doGetCard()
{
	try
	{
		return _service.getCard(_session->_cardNum);
	}
	catch (const std::exception& e)
	{
		throw;
	}
}
