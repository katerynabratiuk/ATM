#pragma once

#include <QWidget>
#include "ui_DepositWidget.h"

#include "frontend/IPage.h"
#include "backend/enums/Pages.h"

class DepositWidget : public QWidget, public IPage
{
	Q_OBJECT
	Q_INTERFACES(IPage)
public:
	DepositWidget(QWidget *parent = nullptr);
	~DepositWidget();

	void doOnDigit(int digit) override;
	void doOnEnter() override;
	void doOnClear() override;
	void doOnCancel() override;

signals:
	void changePage(Pages);

private:
	Ui::DepositWidgetClass _ui;

	// ICardController& _cardController;

	void clean();
	void deposit();
};


