#include "EnterPinWidget.h"
#include "backend/enums/Exceptions.h"

EnterPinWidget::EnterPinWidget(ICardController& cardController, QWidget * parent) 
	: QWidget(parent), _cardController(cardController), _attemptsLeft(3)
{
	_ui.setupUi(this);

	_ui.label->setText("  KishkaBabusi");
	_ui.label->setStyleSheet("QLabel { background-color : purple; color : white; }");

	_ui.pinForm->setReadOnly(true);
	_ui.pinForm->setMaxLength(4);
	_ui.errorInfo->setStyleSheet("color: red;");

	_ui.pinForm->setEchoMode(QLineEdit::Password);
	_ui.pinForm->setValidator(new QRegularExpressionValidator(QRegularExpression("^\\d{4}$"), _ui.pinForm));

	clean();
}

EnterPinWidget::~EnterPinWidget()
{}

void EnterPinWidget::doOnDigit(int digit)
{
	_ui.pinForm->insert(QString::number(digit));
}

void EnterPinWidget::doOnEnter()
{
	authenticate();
}

void EnterPinWidget::doOnClear()
{
	_ui.pinForm->backspace();
}

void EnterPinWidget::doOnCancel()
{
	clean();
	emit changePage(Pages::EnterCardPage);
}

void EnterPinWidget::authenticate()
{
	if (!_ui.pinForm->hasAcceptableInput())
	{
		_ui.errorInfo->setText("Please enter a 4-digit PIN.");
		return;
	}

	try
	{
		_cardController.authenticate(_ui.pinForm->text().toStdString());

		clean();

		emit changePage(Pages::MainMenuPage);
	}
	catch (Exceptions e)
	{
		if (e == Exceptions::AccessDenied)
		{
			_attemptsLeft--;
			if (_attemptsLeft <= 0)
			{
				doOnCancel();
				return;
			}

			_ui.errorInfo->setText("Incorrect PIN. Attempts left: " +
				QString::number(_attemptsLeft) + '.');
		}
		else
		{
			_ui.errorInfo->setText("An unexpected error occurred. Please try again.");
		}
	}
}

void EnterPinWidget::clean()
{
	_ui.pinForm->clear();
	_ui.errorInfo->clear();
	_attemptsLeft = 3;
}

