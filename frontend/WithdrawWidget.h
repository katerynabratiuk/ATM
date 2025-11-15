#pragma once

#include <QWidget>
#include "ui_WithdrawWidget.h"

#include "frontend/IPage.h"
#include "backend/enums/Pages.h"
#include "backend/controllers/ICardController.h"

class WithdrawWidget : public QWidget, public IPage
{
	Q_OBJECT
	Q_INTERFACES(IPage)
public:
	WithdrawWidget(ICardController& cardController, QWidget *parent = nullptr);
	~WithdrawWidget();

	void doOnDigit(int digit) override;
	void doOnEnter() override;
	void doOnClear() override;
	void doOnCancel() override;

signals:
	void changePage(Pages);

private:
	Ui::WithdrawWidgetClass _ui;

	ICardController& _cardController;

	void clean();
	void withdraw();
};

