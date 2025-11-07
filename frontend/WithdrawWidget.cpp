#include "WithdrawWidget.h"

WithdrawWidget::WithdrawWidget(QWidget *parent) : QWidget(parent)
{
	_ui.setupUi(this);

	_ui.amountForm->setReadOnly(true);
	_ui.errorInfo->clear();
	_ui.errorInfo->setStyleSheet("color: red;");
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
	_ui.amountForm->clear();
	emit changePage(Pages::MainMenuPage);
}

void WithdrawWidget::withdraw()
{
	try
	{
		//_cardController->withdraw(_ui.amountForm->text().toInt());

		_ui.amountForm->clear();

		emit changePage(Pages::SuccessPage);
	}
	catch (const std::exception& e)
	{
		_ui.errorInfo->setText("error!!!");
	}
}

