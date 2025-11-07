#include "WithdrawWidget.h"

WithdrawWidget::WithdrawWidget(QStackedWidget* parentStack, QWidget *parent)
	: QWidget(parent), _parentStack(parentStack)
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
	if (_parentStack == nullptr || _parentStack->currentWidget() != this) return;
	_ui.amountForm->insert(QString::number(digit));
}

void WithdrawWidget::doOnEnter()
{
	if (_parentStack == nullptr || _parentStack->currentWidget() != this) return;
	withdraw();
}

void WithdrawWidget::doOnClear()
{
	if (_parentStack == nullptr || _parentStack->currentWidget() != this) return;
	_ui.amountForm->backspace();
}

void WithdrawWidget::doOnCancel()
{
	if (_parentStack == nullptr || _parentStack->currentWidget() != this) return;
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

