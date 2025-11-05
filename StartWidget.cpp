#include "StartWidget.h"

StartWidget::StartWidget(QWidget *parent)
	: QWidget(parent)
{
	_ui.setupUi(this);

	connect(_ui.btnStart, &QPushButton::clicked, this, &StartWidget::on_btnStart_clicked);
}

StartWidget::~StartWidget()
{}

void StartWidget::on_btnStart_clicked()
{
	emit changePage(Pages::LoginPage);
}

