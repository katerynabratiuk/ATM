#include "WithdrawWidget.h"

WithdrawWidget::WithdrawWidget(QWidget *parent) : QWidget(parent)
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
	if (_ui.amountForm->text().isEmpty())
	{
		_ui.errorInfo->setText("Please enter an amount to withdraw.");
		return;
	}

	try
	{
		//_cardController->withdraw(_ui.amountForm->text().toInt());

		clean();

		emit changePage(Pages::SuccessPage);
	}
	catch (const std::exception& e)
	{
		_ui.errorInfo->setText("error!!!");
	}
}

void WithdrawWidget::clean()
{
	_ui.amountForm->clear();
	_ui.errorInfo->clear();
}

