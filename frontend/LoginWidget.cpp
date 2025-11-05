#include "frontend/LoginWidget.h"

LoginWidget::LoginWidget(QWidget *parent, ICardController* cardController)
	: QWidget(parent), _cardController(cardController)
{
	_ui.setupUi(this);

	_ui.errorInfo->setStyleSheet("color: red;");

	_ui.pinForm->setEchoMode(QLineEdit::Password);
	_ui.cardForm->setValidator(new QRegularExpressionValidator(QRegularExpression("^\\d{13}$")));
	_ui.pinForm->setValidator(new QRegularExpressionValidator(QRegularExpression("^\\d{4}$")));

	connect(_ui.btnOk, &QPushButton::clicked, this, &LoginWidget::on_btnOk_clicked);
}

LoginWidget::~LoginWidget()
{}

void LoginWidget::login()
{
	if (!_ui.cardForm->hasAcceptableInput() || !_ui.pinForm->hasAcceptableInput())
	{
		_ui.errorInfo->setText("Please enter a 13-digit card number and a 4-digit PIN.");
		if (!_ui.cardForm->hasAcceptableInput())
		{
			_ui.cardForm->setFocus();
		}
		else
		{
			_ui.pinForm->setFocus();
		}
		return;
	}

	int attempts = 0;
	try
	{
		_cardController->authenticate(_ui.cardForm->text().toStdString(),
			_ui.pinForm->text().toStdString());

		_ui.cardForm->clear();
		_ui.pinForm->clear();
		
		emit changePage(Pages::MainMenuPage);
	}
	catch (const std::exception& e)
	{
		_ui.errorInfo->setText("error!!!");
	}
}

void LoginWidget::on_btnOk_clicked()
{
	login();
}

