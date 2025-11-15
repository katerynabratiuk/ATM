#pragma once

#include <QWidget>
#include "ui_ChangePinWidget.h"
#include <QRegularExpressionValidator>

#include "backend/enums/Pages.h"
#include "frontend/IPage.h"
#include "backend/controllers/ICardController.h"

class ChangePinWidget : public QWidget, public IPage
{
	Q_OBJECT
	Q_INTERFACES(IPage)
public:
	ChangePinWidget(ICardController& cardController, QWidget *parent = nullptr);
	~ChangePinWidget();

	void doOnDigit(int digit) override;
	void doOnEnter() override;
	void doOnClear() override;
	void doOnCancel() override;

signals:
	void changePage(Pages);

private:
	Ui::ChangePinWidgetClass _ui;

	ICardController& _cardController;

	void clean();
	void change();
};

