#pragma once

#include <QWidget>
#include "ui_HistoryWidget.h"

#include "backend/enums/Pages.h"
#include "frontend/IPage.h"

class HistoryWidget : public QWidget, public IPage
{
	Q_OBJECT
	Q_INTERFACES(IPage)
public:
	HistoryWidget(QWidget *parent = nullptr);
	~HistoryWidget();

	void doOnEnter() override;
	void doOnCancel() override;

signals:
	void changePage(Pages);

private:
	Ui::HistoryWidgetClass _ui;
};

