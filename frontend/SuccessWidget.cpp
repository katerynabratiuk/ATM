#include "SuccessWidget.h"

SuccessWidget::SuccessWidget(QWidget *parent)
	: QWidget(parent)
{
	_ui.setupUi(this);
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
