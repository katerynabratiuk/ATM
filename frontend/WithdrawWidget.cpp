#include "WithdrawWidget.h"
#include "backend/enums/Exceptions.h"

WithdrawWidget::WithdrawWidget(ICardController& cardController, QWidget *parent) 
	: QWidget(parent), _cardController(cardController)
{
	_ui.setupUi(this);

	_ui.label->setText("  KishkaBabusi");
	_ui.label->setStyleSheet("QLabel { background-color : purple; color : white; }");

	_ui.amountForm->setReadOnly(true);
	_ui.errorInfo->setStyleSheet("color: red;");

	clean();
}

WithdrawWidget::~WithdrawWidget()
{}

void WithdrawWidget::doOnDigit(int digit)
{
	_ui.amountForm->insert(QString::number(digit));
}

void WithdrawWidget::doOnEnter()
{
	withdraw();
}

void WithdrawWidget::doOnClear()
{
	_ui.amountForm->backspace();
}

void WithdrawWidget::doOnCancel()
{
	clean();
	emit changePage(Pages::MainMenuPage);
}

void WithdrawWidget::withdraw()
{
	if (_ui.amountForm->text().isEmpty() || _ui.amountForm->text().toInt() <= 0)
	{
		_ui.errorInfo->setText("Please enter an amount to withdraw.");
		return;
	}

	if (_ui.amountForm->text().toInt() % 10 != 0)
	{
		_ui.errorInfo->setText("No available banknotes for this amount.");
		return;
	}

	try
	{
		_cardController.withdraw(_ui.amountForm->text().toInt());

		clean();

		emit changePage(Pages::SuccessPage);
	}
	catch (Exceptions e)
	{
		if (e == Exceptions::NotEnoughMoney)
		{
			_ui.errorInfo->setText("Not enough money.");
		}
		else if (e == Exceptions::NoSuchCash)
		{
			_ui.errorInfo->setText("No available banknotes for this amount.");
		}
		else
		{
			_ui.errorInfo->setText("An unexpected error occurred. Please try again.");
		}
	}
}

void WithdrawWidget::clean()
{
	_ui.amountForm->clear();
	_ui.errorInfo->clear();
}

