#pragma once

#include <QWidget>
#include <QRegularExpressionValidator>
#include "ui_LoginWidget.h"
#include "ICardController.h"
#include "Enums.h"

class LoginWidget : public QWidget
{
	Q_OBJECT

public:
	LoginWidget(QWidget *parent = nullptr, ICardController* cardController = nullptr);
	~LoginWidget();

private slots:
	void on_btnOk_clicked();

signals:
	void changePage(Pages);

private:
	Ui::LoginWidgetClass _ui;

	ICardController* _cardController;

	void login();
};

