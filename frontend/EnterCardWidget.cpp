#include "EnterCardWidget.h"
#include "EnterPinWidget.h"

EnterCardWidget::EnterCardWidget(QStackedWidget* parentStack, QWidget* parent)
	: QWidget(parent), _parentStack(parentStack)
{
	_ui.setupUi(this);

	_ui.cardForm->setReadOnly(true);
	_ui.cardForm->setMaxLength(13);
	_ui.errorInfo->clear();
	_ui.errorInfo->setStyleSheet("color: red;");

	_ui.cardForm->setValidator(new QRegularExpressionValidator(QRegularExpression("^\\d{13}$"), _ui.cardForm));
}

EnterCardWidget::~EnterCardWidget()
{}

void EnterCardWidget::doOnDigit(int digit)
{
	if (_parentStack == nullptr || _parentStack->currentWidget() != this) return;
	_ui.cardForm->insert(QString::number(digit));
}

void EnterCardWidget::doOnEnter()
{
	if (_parentStack == nullptr || _parentStack->currentWidget() != this) return;
	setCard();
}

void EnterCardWidget::doOnClear()
{
	if (_parentStack == nullptr || _parentStack->currentWidget() != this) return;
	_ui.cardForm->backspace();
}

void EnterCardWidget::doOnCancel()
{
	if (_parentStack == nullptr || _parentStack->currentWidget() != this) return;
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
	catch (const std::exception& e)
	{
		_ui.errorInfo->setText("error!!!");
	}
}

void EnterCardWidget::clean()
{
	_ui.cardForm->clear();
	_ui.errorInfo->clear();
}