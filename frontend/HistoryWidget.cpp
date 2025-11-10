#include "HistoryWidget.h"

HistoryWidget::HistoryWidget(QWidget *parent)
	: QWidget(parent)
{
	_ui.setupUi(this);

	_ui.label->setText("  KishkaBabusi");
	_ui.label->setStyleSheet("QLabel { background-color : purple; color : white; }");
}

HistoryWidget::~HistoryWidget()
{}

void HistoryWidget::doOnEnter()
{
	emit changePage(Pages::MainMenuPage);
}

void HistoryWidget::doOnCancel()
{
	emit changePage(Pages::MainMenuPage);
}

