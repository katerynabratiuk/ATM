#include "TransferWidget.h"

TransferWidget::TransferWidget(QWidget* parent)
	: QWidget(parent), _top(true)
{
	_ui.setupUi(this);

	_ui.optMove->setText("   UP\nDOWN");
	_ui.optMove->setStyleSheet("QLabel { background-color : gray; color : black; }");

	_ui.amountForm->setReadOnly(true);
	_ui.cardForm->setReadOnly(true);
	_ui.cardForm->setMaxLength(13);
	_ui.errorInfo->setStyleSheet("color: red;");

	_ui.cardForm->setValidator(new QRegularExpressionValidator(QRegularExpression("^\\d{13}$"), _ui.cardForm));

	clean();
}

TransferWidget::~TransferWidget()
{
}

void TransferWidget::doOnDigit(int digit)
{
	if (_top)
	{
		_ui.cardForm->insert(QString::number(digit));
	}
	else
	{
		_ui.amountForm->insert(QString::number(digit));
	}
}

void TransferWidget::doOnEnter()
{
	transfer();
}

void TransferWidget::doOnClear()
{
	if (_top)
	{
		_ui.cardForm->backspace();
	}
	else
	{
		_ui.amountForm->backspace();
	}
}

void TransferWidget::doOnCancel()
{
	clean();
	emit changePage(Pages::MainMenuPage);
}

void TransferWidget::doOnSideButton(bool rightSide, int index)
{
	if (rightSide && index == 2)
	{
		_top = !_top;
	}
}

void TransferWidget::transfer()
{
	if (!_ui.cardForm->hasAcceptableInput())
	{
		_ui.errorInfo->setText("Please enter a 13-digit card number.");
		return;
	}
	if (_ui.amountForm->text().isEmpty())
	{
		_ui.errorInfo->setText("Please enter an amount to transfer.");
		return;
	}

	try
	{
		//_cardController->transfer(_ui.cardForm->text().toStdString(), 
		// _ui.amountForm->text().toInt());

		clean();

		emit changePage(Pages::SuccessPage);
	}
	catch (const std::exception& e)
	{
		_ui.errorInfo->setText("error!!!");
	}
}

void TransferWidget::clean()
{
	_top = true;
	_ui.cardForm->clear();
	_ui.amountForm->clear();
	_ui.errorInfo->clear();
}