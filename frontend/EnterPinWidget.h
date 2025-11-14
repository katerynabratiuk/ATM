#pragma once

#include <QWidget>
#include "ui_EnterPinWidget.h"
#include <QRegularExpressionValidator>

#include "backend/enums/Pages.h"
#include "frontend/IPage.h"
#include "backend/controllers/ICardController.h"

class EnterPinWidget : public QWidget, public IPage
{
	Q_OBJECT
	Q_INTERFACES(IPage)
public:
	EnterPinWidget(ICardController& cardController, QWidget* parent = nullptr);
	~EnterPinWidget();

	void doOnDigit(int digit) override;
	void doOnEnter() override;
	void doOnClear() override;
	void doOnCancel() override;

signals:
	void changePage(Pages);

private:
	Ui::EnterPinWidgetClass _ui;

	ICardController& _cardController;

	void clean();
	void authenticate();
};

