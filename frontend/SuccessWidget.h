#pragma once

#include <QWidget>
#include "ui_SuccessWidget.h"

#include "backend/Enums.h"
#include "frontend/IPage.h"

class SuccessWidget : public QWidget, public IPage
{
	Q_OBJECT
	Q_INTERFACES(IPage)
public:
	SuccessWidget(QWidget *parent = nullptr);
	~SuccessWidget();

	void doOnEnter() override;
	void doOnCancel() override;

signals:
	void changePage(Pages);

private:
	Ui::SuccessWidgetClass _ui;
};

