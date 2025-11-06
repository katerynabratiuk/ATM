#include "EnterPinWidget.h"

EnterPinWidget::EnterPinWidget(QStackedWidget* parentStack, QWidget * parent)
	: QWidget(parent), _parentStack(parentStack)
{
	_ui.setupUi(this);

	_ui.pinForm->setReadOnly(true);
	_ui.pinForm->setMaxLength(4);
	_ui.errorInfo->clear();
	_ui.errorInfo->setStyleSheet("color: red;");

	_ui.pinForm->setEchoMode(QLineEdit::Password);
	_ui.pinForm->setValidator(new QRegularExpressionValidator(QRegularExpression("^\\d{4}$"), _ui.pinForm));
}

EnterPinWidget::~EnterPinWidget()
{}

void EnterPinWidget::onDigit(int digit)
{
	if (_parentStack->currentWidget() != this) return;
	_ui.pinForm->insert(QString::number(digit));
}

void EnterPinWidget::onEnter()
{
	if (_parentStack->currentWidget() != this) return;
	authenticate();
}

void EnterPinWidget::onClear()
{
	if (_parentStack->currentWidget() != this) return;
	_ui.pinForm->backspace();
}

void EnterPinWidget::onCancel()
{
	if (_parentStack->currentWidget() != this) return;
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
		//_cardController->authenticate(_ui.pinForm->text().toStdString());

		clean();

		emit changePage(Pages::MainMenuPage);
	}
	catch (const std::exception& e)
	{
		_ui.errorInfo->setText("error!!!");
	}
}

void EnterPinWidget::clean()
{
	_ui.pinForm->clear();
	_ui.errorInfo->clear();
}

