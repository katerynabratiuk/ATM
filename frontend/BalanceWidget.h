#pragma once

#include <QWidget>
#include "ui_BalanceWidget.h"

#include "backend/Enums.h"
#include "frontend/IPage.h"
#include "backend/Models.h"

class BalanceWidget : public QWidget, public IPage
{
	Q_OBJECT
	Q_INTERFACES(IPage)
public:
	BalanceWidget(QWidget *parent = nullptr);
	~BalanceWidget();

	void doOnEnter() override;
	void doOnCancel() override;

	void show();

signals:
	void changePage(Pages);

private:
	Ui::BalanceWidgetClass _ui;
	// ICardController& _cardController;
};

