#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ATMSimulator.h"

#include "frontend/EnterCardWidget.h"
#include "frontend/EnterPinWidget.h"
#include "frontend/MainMenuWidget.h"
#include "frontend/WithdrawWidget.h"
#include "frontend/TransferWidget.h"
#include "frontend/DepositWidget.h"
#include "frontend/ChangePinWidget.h"
#include "frontend/SuccessWidget.h"
#include "backend/controllers/ICardController.h"
#include "backend/Enums.h"
#include "frontend/IPage.h"

class ATMInterface : public QMainWindow
{
    Q_OBJECT

public:
    ATMInterface(QWidget *parent = nullptr);
    ~ATMInterface();

private slots:
    void changeCurrentPage(Pages);

    void on_btnLeft1_clicked();
    void on_btnLeft2_clicked();
    void on_btnLeft3_clicked();
    void on_btnRight1_clicked();
    void on_btnRight2_clicked();
    void on_btnRight3_clicked();

    void on_btn0_clicked();
    void on_btn1_clicked();
    void on_btn2_clicked();
    void on_btn3_clicked();
    void on_btn4_clicked();
    void on_btn5_clicked();
    void on_btn6_clicked();
    void on_btn7_clicked();
    void on_btn8_clicked();
    void on_btn9_clicked();

    void on_btnEnter_clicked();
    void on_btnClear_clicked();
    void on_btnCancel_clicked();

    void forwardDigit(int digit);
    void forwardEnter();
    void forwardClear();
    void forwardCancel();
    void forwardSideButton(bool rightSide, int index);

signals:
    void digitPressed(int digit);
    void enterPressed();
    void clearPressed();
    void cancelPressed();
    void sideButtonPressed(bool rightSide, int index);

private:
    Ui::ATMInterfaceClass _ui;

    // ICardController& _cardController;

    EnterCardWidget _cardPage;
    EnterPinWidget _enterPinPage;
	MainMenuWidget _mainMenuPage;
    WithdrawWidget _withdrawPage;
	DepositWidget _depositPage;
	TransferWidget _transferPage;
    ChangePinWidget _changePinPage;
	SuccessWidget _successPage;

    void addPages();
    void connectSlots();
};

