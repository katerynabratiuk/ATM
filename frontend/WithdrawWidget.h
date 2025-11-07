#pragma once

#include <QWidget>
#include "ui_WithdrawWidget.h"

#include "frontend/IPage.h"
#include "backend/Enums.h"

class WithdrawWidget : public QWidget, public IPage
{
	Q_OBJECT
	Q_INTERFACES(IPage)
public:
	WithdrawWidget(QWidget *parent = nullptr);
	~WithdrawWidget();

	void doOnDigit(int digit) override;
	void doOnEnter() override;
	void doOnClear() override;
	void doOnCancel() override;

signals:
	void changePage(Pages);

private:
	Ui::WithdrawWidgetClass _ui;

	// ICardController& _cardController;

	void withdraw();
};

