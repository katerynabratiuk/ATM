#include "MainMenuWidget.h"

MainMenuWidget::MainMenuWidget(QWidget *parent)
	: QWidget(parent)
{
	_ui.setupUi(this);

	connect(_ui.btnWithdraw, &QPushButton::clicked, this, &MainMenuWidget::on_btnWithdraw_clicked);
	connect(_ui.btnDeposit, &QPushButton::clicked, this, &MainMenuWidget::on_btnDeposit_clicked);
	connect(_ui.btnTransfer, &QPushButton::clicked, this, &MainMenuWidget::on_btnTransfer_clicked);
	connect(_ui.btnPin, &QPushButton::clicked, this, &MainMenuWidget::on_btnPin_clicked);
	connect(_ui.btnHistory, &QPushButton::clicked, this, &MainMenuWidget::on_btnHistory_clicked);
}

MainMenuWidget::~MainMenuWidget()
{}

void MainMenuWidget::on_btnWithdraw_clicked()
{
	emit changePage(Pages::WithdrawPage);
}

void MainMenuWidget::on_btnDeposit_clicked()
{
	emit changePage(Pages::DepositPage);
}

void MainMenuWidget::on_btnTransfer_clicked()
{
	emit changePage(Pages::TransferPage);
}

void MainMenuWidget::on_btnPin_clicked()
{
	emit changePage(Pages::ChangePinPage);
}

void MainMenuWidget::on_btnHistory_clicked()
{
	emit changePage(Pages::HistoryPage);
}

