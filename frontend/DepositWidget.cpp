#include "DepositWidget.h"
#include "backend/enums/Exceptions.h"

DepositWidget::DepositWidget(ICardController& cardController, QWidget *parent)
	: QWidget(parent), _cardController(cardController)
{
	_ui.setupUi(this);

	_ui.label->setText("  KishkaBabusi");
	_ui.label->setStyleSheet("QLabel { background-color : purple; color : white; }");

	_ui.amountForm->setReadOnly(true);
	_ui.errorInfo->setStyleSheet("color: red;");

	clean();
}

DepositWidget::~DepositWidget()
{}

void DepositWidget::doOnDigit(int digit)
{
	_ui.amountForm->insert(QString::number(digit));
}

void DepositWidget::doOnEnter()
{
	deposit();
}

void DepositWidget::doOnClear()
{
	_ui.amountForm->backspace();
}

void DepositWidget::doOnCancel()
{
	clean();
	emit changePage(Pages::MainMenuPage);
}

void DepositWidget::deposit()
{
	if (_ui.amountForm->text().isEmpty())
	{
		_ui.errorInfo->setText("Please enter an amount to deposit.");
		return;
	}

	if (_ui.amountForm->text().toInt() % 10 != 0)
	{
		_ui.errorInfo->setText("Please enter legit banknotes.");
		return;
	}

	try
	{
		_cardController.deposit(_ui.amountForm->text().toInt());

		clean();

		emit changePage(Pages::SuccessPage);
	}
	catch (Exceptions e)
	{
		_ui.errorInfo->setText("An unexpected error occurred. Please try again.");
	}
}

void DepositWidget::clean()
{
	_ui.amountForm->clear();
	_ui.errorInfo->clear();
}

