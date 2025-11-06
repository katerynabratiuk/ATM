#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ATMSimulator.h"

#include "frontend/LoginWidget.h"
#include "frontend/StartWidget.h"
#include "frontend/MainMenuWidget.h"

#include "backend/controllers/ICardController.h"
#include "backend/Enums.h"

class ATMInterface : public QMainWindow
{
    Q_OBJECT

public:
    ATMInterface(/*ICardController& cardController, */QWidget *parent = nullptr);
    ~ATMInterface();

private slots:
	void changeCurrentPage(Pages);

private:
    Ui::ATMInterfaceClass _ui;

    // ICardController& _cardController;

	StartWidget _startPage;
    LoginWidget _loginPage;
    MainMenuWidget _mainMenuPage;

    void addPages();
	void connectSlots();
};

