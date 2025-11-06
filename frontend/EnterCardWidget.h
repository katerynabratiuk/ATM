#pragma once

#include <QWidget>
#include <QStackedWidget>
#include "ui_EnterCardWidget.h"
#include <QRegularExpressionValidator>

#include "backend/Enums.h"
#include "frontend/IPage.h"

class EnterCardWidget : public QWidget, public IPage
{
	Q_OBJECT
	Q_INTERFACES(IPage)
public:
	EnterCardWidget(QStackedWidget* parentStack, QWidget* parent = nullptr);
	~EnterCardWidget();

	void doOnDigit(int digit) override;
	void doOnEnter() override;
	void doOnClear() override;
	void doOnCancel() override;

signals:
	void changePage(Pages);

private:
	Ui::EnterCardWidgetClass _ui;
	QStackedWidget* _parentStack;

	// ICardController& _cardController;

	void clean();
	void setCard();
};

