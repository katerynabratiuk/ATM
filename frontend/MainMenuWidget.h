#pragma once

#include <QWidget>
#include <QStackedWidget>
#include "ui_MainMenuWidget.h"

#include "frontend/IPage.h"
#include "backend/enums/Pages.h"

class MainMenuWidget : public QWidget, public IPage
{
	Q_OBJECT
	Q_INTERFACES(IPage)
public:
	MainMenuWidget(QWidget* parent = nullptr);
	~MainMenuWidget();

	void doOnSideButton(bool rightSide, int index) override;
	void doOnCancel() override;

signals:
	void changePage(Pages);

private:
	Ui::MainMenuWidgetClass _ui;
};

