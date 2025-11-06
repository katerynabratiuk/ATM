#pragma once

#include <QWidget>
#include <QRegularExpressionValidator>

#include "ui_LoginWidget.h"

#include "backend/controllers/ICardController.h"
#include "backend/Enums.h"

class LoginWidget : public QWidget
{
	Q_OBJECT

public:
	LoginWidget(/*ICardController& cardController, */QWidget *parent = nullptr);
	~LoginWidget();

private slots:
	void on_btnOk_clicked();

signals:
	void changePage(Pages);

private:
	Ui::LoginWidgetClass _ui;

	// ICardController& _cardController;

	void login();
};

