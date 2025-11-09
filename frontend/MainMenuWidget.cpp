#include "MainMenuWidget.h"

MainMenuWidget::MainMenuWidget(QWidget *parent) : QWidget(parent)
{
	_ui.setupUi(this);

	_ui.label->setText("  KishkaBabusi");
	_ui.label->setStyleSheet("QLabel { background-color : purple; color : white; }");

	_ui.optWithdraw->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	_ui.optDeposit->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	_ui.optTransfer->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	_ui.optHistory->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	_ui.optBalance->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	_ui.optPin->setAttribute(Qt::WA_TransparentForMouseEvents, true);

	//_ui.optWithdraw->setStyleSheet("QPushButton { text-align: left; padding-left: 5; }");
	//_ui.optDeposit->setStyleSheet("QPushButton { text-align: left; padding-left: 5; }");
	//_ui.optTransfer->setStyleSheet("QPushButton { text-align: left; padding-left: 5; }");
	//_ui.optHistory->setStyleSheet("QPushButton { text-align: right; padding-right: 5; }");
	//_ui.optBalance->setStyleSheet("QPushButton { text-align: right; padding-right: 5; }");
	//_ui.optPin->setStyleSheet("QPushButton { text-align: right; padding-right: 5; }");
}

MainMenuWidget::~MainMenuWidget()
{}

void MainMenuWidget::doOnSideButton(bool rightSide, int index)
{
	if (rightSide)
	{
		switch (index)
		{
		case 1:
			emit changePage(Pages::ChangePinPage);
			break;
		case 2:
			emit changePage(Pages::HistoryPage);
			break;
		case 3:
			emit changePage(Pages::BalancePage);
			break;
		default:
			break;
		}
	}
	else
	{
		switch (index)
		{
		case 1:
			emit changePage(Pages::WithdrawPage);
			break;
		case 2:
			emit changePage(Pages::DepositPage);
			break;
		case 3:
			emit changePage(Pages::TransferPage);
			break;
		default:
			break;
		}
	}
}

void MainMenuWidget::doOnCancel()
{
	emit changePage(Pages::EnterCardPage);
}

