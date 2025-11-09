#include "SuccessWidget.h"

SuccessWidget::SuccessWidget(QWidget *parent)
	: QWidget(parent)
{
	_ui.setupUi(this);

	_ui.label->setText("  KishkaBabusi");
	_ui.label->setStyleSheet("QLabel { background-color : purple; color : white; }");
}

SuccessWidget::~SuccessWidget()
{}

void SuccessWidget::doOnEnter()
{
	emit changePage(Pages::MainMenuPage);
}

void SuccessWidget::doOnCancel()
{
	emit changePage(Pages::MainMenuPage);
}
