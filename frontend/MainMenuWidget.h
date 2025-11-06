#pragma once

#include <QWidget>
#include "ui_MainMenuWidget.h"

#include "backend/Enums.h"

class MainMenuWidget : public QWidget
{
	Q_OBJECT

public:
	MainMenuWidget(QWidget *parent = nullptr);
	~MainMenuWidget();

private slots:
	void on_btnWithdraw_clicked();
	void on_btnDeposit_clicked();
	void on_btnTransfer_clicked();
	void on_btnPin_clicked();
	void on_btnHistory_clicked();

signals:
	void changePage(Pages);

private:
	Ui::MainMenuWidgetClass _ui;
};

