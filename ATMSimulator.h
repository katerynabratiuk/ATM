#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ATMSimulator.h"

class ATMSimulator : public QMainWindow
{
    Q_OBJECT

public:
    ATMSimulator(QWidget *parent = nullptr);
    ~ATMSimulator();

private:
    Ui::ATMSimulatorClass ui;
};

