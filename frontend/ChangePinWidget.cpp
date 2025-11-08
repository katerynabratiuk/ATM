#include "ChangePinWidget.h"

ChangePinWidget::ChangePinWidget(QWidget *parent)
	: QWidget(parent)
{
	_ui.setupUi(this);

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
		//_cardController->changePin(_ui.pinForm->text().toStdString());

		clean();

		emit changePage(Pages::SuccessPage);
	}
	catch (const std::exception& e)
	{
		_ui.errorInfo->setText("error!!!");
	}
}

void ChangePinWidget::clean()
{
	_ui.pinForm->clear();
	_ui.errorInfo->clear();
}

