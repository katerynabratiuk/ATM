#pragma once

#include <QWidget>
#include "ui_WithdrawWidget.h"
#include <QStackedWidget>

#include "frontend/IPage.h"
#include "backend/Enums.h"

class WithdrawWidget : public QWidget, public IPage
{
	Q_OBJECT
	Q_INTERFACES(IPage)
public:
	WithdrawWidget(QStackedWidget* parentStack, QWidget *parent = nullptr);
	~WithdrawWidget();

	void doOnDigit(int digit) override;
	void doOnEnter() override;
	void doOnClear() override;
	void doOnCancel() override;

signals:
	void changePage(Pages);

private:
	Ui::WithdrawWidgetClass _ui;
	QStackedWidget* _parentStack;

	// ICardController& _cardController;

	void withdraw();
};

