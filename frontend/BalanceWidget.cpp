#include "BalanceWidget.h"
#include "backend/enums/Exceptions.h"

BalanceWidget::BalanceWidget(QWidget *parent)
	: QWidget(parent)
{
	_ui.setupUi(this);

	_ui.label->setText("  KishkaBabusi");
	_ui.label->setStyleSheet("QLabel { background-color : purple; color : white; }");
}

BalanceWidget::~BalanceWidget()
{}

void BalanceWidget::doOnEnter()
{
	emit changePage(Pages::MainMenuPage);
}

void BalanceWidget::doOnCancel()
{
	emit changePage(Pages::MainMenuPage);
}

void BalanceWidget::show()
{
	try
	{
		Card card/* = _cardController.getCard()*/;
		_ui.clValue->setText("not a credit card");

		atm::money::Money available = card._balance;
		if (card._creditLimit > 0)
		{
			available = card._creditLimit - card._balance;

			_ui.clValue->setText(
				QString::fromStdString(atm::money::to_string(card._creditLimit)) + " uah"
			);
		}
		_ui.bValue->setText(
			QString::fromStdString(atm::money::to_string(available)) + " uah"
		);
	}
	catch (Exceptions e)
	{
		_ui.bValue->setText("error");
		_ui.clValue->setText("error");
	}
}

