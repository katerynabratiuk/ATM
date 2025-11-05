#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ATMSimulator.h"
#include "LoginWidget.h"
#include "StartWidget.h"
#include "ICardController.h"
#include "Enums.h"

class ATMInterface : public QMainWindow
{
    Q_OBJECT

public:
    ATMInterface(QWidget *parent = nullptr, ICardController* cardController = nullptr);
    ~ATMInterface();

private slots:
	void changeCurrentPage(Pages);

private:
    Ui::ATMInterfaceClass _ui;

    ICardController* _cardController;

    LoginWidget _loginPage;
	StartWidget _startPage;

    void addPages();
	void connectSlots();
};

