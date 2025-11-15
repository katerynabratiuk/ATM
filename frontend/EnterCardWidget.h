#pragma once

#include <QWidget>
#include "ui_EnterCardWidget.h"
#include <QRegularExpressionValidator>

#include "backend/enums/Pages.h"
#include "frontend/IPage.h"
#include "backend/controllers/ICardController.h"

class EnterCardWidget : public QWidget, public IPage
{
	Q_OBJECT
	Q_INTERFACES(IPage)
public:
	EnterCardWidget(ICardController& cardController, QWidget* parent = nullptr);
	~EnterCardWidget();

	void doOnDigit(int digit) override;
	void doOnEnter() override;
	void doOnClear() override;
	void doOnCancel() override;

signals:
	void changePage(Pages);

private:
	Ui::EnterCardWidgetClass _ui;

	ICardController& _cardController;

	void clean();
	void setCard();
};

