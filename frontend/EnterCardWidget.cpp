#include "EnterCardWidget.h"
#include "EnterPinWidget.h"
#include "backend/Exceptions.h"

EnterCardWidget::EnterCardWidget(QWidget* parent) : QWidget(parent)
{
	_ui.setupUi(this);

	_ui.label->setText("  KishkaBabusi");
	_ui.label->setStyleSheet("QLabel { background-color : purple; color : white; }");

	_ui.cardForm->setReadOnly(true);
	_ui.cardForm->setMaxLength(13);
	_ui.errorInfo->setStyleSheet("color: red;");

	_ui.cardForm->setValidator(new QRegularExpressionValidator(QRegularExpression("^\\d{13}$"), _ui.cardForm));

	clean();
}

EnterCardWidget::~EnterCardWidget()
{}

void EnterCardWidget::doOnDigit(int digit)
{
	_ui.cardForm->insert(QString::number(digit));
}

void EnterCardWidget::doOnEnter()
{
	setCard();
}

void EnterCardWidget::doOnClear()
{
	_ui.cardForm->backspace();
}

void EnterCardWidget::doOnCancel()
{
	clean();
}

void EnterCardWidget::setCard()
{
	if (!_ui.cardForm->hasAcceptableInput())
	{
		_ui.errorInfo->setText("Please enter a 13-digit card number.");
		return;
	}

	try
	{
		//_cardController->setCard(_ui.cardForm->text().toStdString());

		clean();

		emit changePage(Pages::EnterPinPage);
	}
	catch (Exceptions e)
	{
		if (e == Exceptions::DoesntExist)
		{
			_ui.errorInfo->setText("Card does not exist.");
		}
		else
		{
			_ui.errorInfo->setText("An unexpected error occurred. Please try again.");
		}
	}
}

void EnterCardWidget::clean()
{
	_ui.cardForm->clear();
	_ui.errorInfo->clear();
}