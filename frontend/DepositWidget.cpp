#include "DepositWidget.h"

DepositWidget::DepositWidget(QWidget *parent)
	: QWidget(parent)
{
	_ui.setupUi(this);

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

	try
	{
		//_cardController->deposit(_ui.amountForm->text().toInt());

		clean();

		emit changePage(Pages::SuccessPage);
	}
	catch (const std::exception& e)
	{
		_ui.errorInfo->setText("error!!!");
	}
}

void DepositWidget::clean()
{
	_ui.amountForm->clear();
	_ui.errorInfo->clear();
}

