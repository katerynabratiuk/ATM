#pragma once

#include <QWidget>
#include "ui_TransferWidget.h"
#include <QRegularExpressionValidator>

#include "backend/enums/Pages.h"
#include "frontend/IPage.h"
#include "backend/controllers/ICardController.h"

class TransferWidget : public QWidget, public IPage
{
	Q_OBJECT
	Q_INTERFACES(IPage)
public:
	TransferWidget(ICardController& cardController, QWidget* parent = nullptr);
	~TransferWidget();

	void doOnDigit(int digit) override;
	void doOnEnter() override;
	void doOnClear() override;
	void doOnCancel() override;
	void doOnSideButton(bool rightSide, int index) override;

signals:
	void changePage(Pages);

private:
	Ui::TransferWidgetClass _ui;

	bool _top;

	ICardController& _cardController;

	void clean();
	void transfer();
};