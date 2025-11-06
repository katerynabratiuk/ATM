#pragma once

#include <QWidget>
#include <QStackedWidget>
#include "ui_EnterPinWidget.h"
#include <QRegularExpressionValidator>

#include "backend/Enums.h"

class EnterPinWidget : public QWidget
{
	Q_OBJECT

public:
	EnterPinWidget(QStackedWidget* parentStack, QWidget* parent = nullptr);
	~EnterPinWidget();

public slots:
	void onDigit(int digit);
	void onEnter();
	void onClear();
	void onCancel();

signals:
	void changePage(Pages);

private:
	Ui::EnterPinWidgetClass _ui;
	QStackedWidget* _parentStack;

	// ICardController& _cardController;

	void clean();
	void authenticate();
};

