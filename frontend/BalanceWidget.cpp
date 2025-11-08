#include "BalanceWidget.h"

BalanceWidget::BalanceWidget(QWidget *parent)
	: QWidget(parent)
{
	_ui.setupUi(this);
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
		_ui.bValue->setText(QString::number(card._balance));
		if (card._creditLimit <= 0)
		{
			_ui.clValue->setText("not a credit card");
		}
	}
	catch (const std::exception& e)
	{
		_ui.bValue->setText("error");
		_ui.clValue->setText("error");
	}
}

