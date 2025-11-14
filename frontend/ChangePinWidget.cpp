#include "ChangePinWidget.h"
#include "backend/enums/Exceptions.h"

ChangePinWidget::ChangePinWidget(ICardController& cardController, QWidget *parent)
	: QWidget(parent), _cardController(cardController)
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

ChangePinWidget::~ChangePinWidget()
{}

void ChangePinWidget::doOnDigit(int digit)
{
	_ui.pinForm->insert(QString::number(digit));
}

void ChangePinWidget::doOnEnter()
{
	change();
}

void ChangePinWidget::doOnClear()
{
	_ui.pinForm->backspace();
}

void ChangePinWidget::doOnCancel()
{
	clean();
	emit changePage(Pages::MainMenuPage);
}

void ChangePinWidget::change()
{
	if (!_ui.pinForm->hasAcceptableInput())
	{
		_ui.errorInfo->setText("Please enter a 4-digit PIN.");
		return;
	}

	try
	{
		_cardController.changePin(_ui.pinForm->text().toStdString());

		clean();

		emit changePage(Pages::SuccessPage);
	}
	catch (Exceptions e)
	{
		if (e == Exceptions::SamePassword)
		{
			_ui.errorInfo->setText("New PIN cannot be the same as the old PIN.");
		}
		else
		{
			_ui.errorInfo->setText("An unexpected error occurred. Please try again.");
		}
	}
}

void ChangePinWidget::clean()
{
	_ui.pinForm->clear();
	_ui.errorInfo->clear();
}

