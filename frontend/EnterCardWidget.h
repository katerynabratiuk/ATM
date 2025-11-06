#pragma once

#include <QWidget>
#include <QStackedWidget>
#include "ui_EnterCardWidget.h"
#include <QRegularExpressionValidator>

#include "backend/Enums.h"

class EnterCardWidget : public QWidget
{
	Q_OBJECT

public:
	EnterCardWidget(/*ICardController& cardController, */QStackedWidget* parentStack, QWidget* parent = nullptr);
	~EnterCardWidget();

public slots:
	void onDigit(int digit);
	void onEnter();
	void onClear();
	void onCancel();

signals:
	void changePage(Pages);

private:
	Ui::EnterCardWidgetClass _ui;
	QStackedWidget* _parentStack;

	// ICardController& _cardController;

	void clean();
	void setCard();
};

