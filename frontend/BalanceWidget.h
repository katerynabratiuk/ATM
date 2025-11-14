#pragma once

#include <QWidget>
#include "ui_BalanceWidget.h"

#include "backend/core/Money.h"
#include "backend/enums/Pages.h"
#include "frontend/IPage.h"
#include "backend/models/Card.h"
#include "backend/controllers/ICardController.h"

class BalanceWidget : public QWidget, public IPage
{
	Q_OBJECT
	Q_INTERFACES(IPage)
public:
	BalanceWidget(ICardController& cardController, QWidget *parent = nullptr);
	~BalanceWidget();

	void doOnEnter() override;
	void doOnCancel() override;

	void show();

signals:
	void changePage(Pages);

private:
	Ui::BalanceWidgetClass _ui;
	ICardController& _cardController;
};

