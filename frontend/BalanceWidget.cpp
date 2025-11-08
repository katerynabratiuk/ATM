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
		_ui.clTitle->setVisible(false);
		_ui.clValue->setVisible(false);

		Card card/* = _cardController.getCard()*/;
		_ui.bValue->setText(QString::number(card._balance));
		if (card._creditLimit > 0)
		{
			_ui.clTitle->setVisible(true);
			_ui.clValue->setVisible(true);
			_ui.clValue->setText(QString::number(card._creditLimit));
		}
	}
	catch (const std::exception& e)
	{
		_ui.bValue->setText("Error!");
	}
}

