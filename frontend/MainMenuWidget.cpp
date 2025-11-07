#include "MainMenuWidget.h"

MainMenuWidget::MainMenuWidget(QStackedWidget* parentStack, QWidget *parent)
	: QWidget(parent), _parentStack(parentStack)
{
	_ui.setupUi(this);

	_ui.optDeposit->setStyleSheet("QLabel { background-color : gray; color : black; }");
	_ui.optWithdraw->setStyleSheet("QLabel { background-color : gray; color : black; }");
	_ui.optTransfer->setStyleSheet("QLabel { background-color : gray; color : black; }");
	_ui.optPin->setStyleSheet("QLabel { background-color : gray; color : black; }");
	_ui.optHistory->setStyleSheet("QLabel { background-color : gray; color : black; }");
}

MainMenuWidget::~MainMenuWidget()
{}

void MainMenuWidget::doOnSideButton(bool rightSide, int index)
{
	if (_parentStack == nullptr || _parentStack->currentWidget() != this) return;
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

