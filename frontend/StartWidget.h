#pragma once

#include <QWidget>
#include "ui_StartWidget.h"

#include "backend/Enums.h"

class StartWidget : public QWidget
{
	Q_OBJECT

public:
	StartWidget(QWidget *parent = nullptr);
	~StartWidget();

private slots:
	void on_btnStart_clicked();

signals:
	void changePage(Pages);

private:
	Ui::StartWidgetClass _ui;
};

