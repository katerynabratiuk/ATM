#include "frontend/ATMInterface.h"

ATMInterface::ATMInterface(QWidget* parent)
	: QMainWindow(parent), _cardPage(nullptr), _pinPage(nullptr)
{
	_ui.setupUi(this);

	addPages();
	connectSlots();

	changeCurrentPage(Pages::EnterCardPage);
}

ATMInterface::~ATMInterface()
{
	delete _cardPage;
	delete _pinPage;
}

void ATMInterface::changeCurrentPage(Pages page)
{
	_ui.widgetStack->setCurrentIndex(static_cast<int>(page));
}

void ATMInterface::addPages()
{
	_cardPage = new EnterCardWidget(_ui.widgetStack);
	_ui.widgetStack->insertWidget(static_cast<int>(Pages::EnterCardPage), _cardPage);

	_pinPage = new EnterPinWidget(_ui.widgetStack);
	_ui.widgetStack->insertWidget(static_cast<int>(Pages::EnterPinPage), _pinPage);
}

void ATMInterface::connectSlots()
{
	connect(_cardPage, &EnterCardWidget::changePage, this, &ATMInterface::changeCurrentPage);
	connect(_pinPage, &EnterPinWidget::changePage, this, &ATMInterface::changeCurrentPage);

	connect(this, &ATMInterface::digitPressed, _pinPage, &EnterPinWidget::onDigit);
	connect(this, &ATMInterface::enterPressed, _pinPage, &EnterPinWidget::onEnter);
	connect(this, &ATMInterface::clearPressed, _pinPage, &EnterPinWidget::onClear);
	connect(this, &ATMInterface::cancelPressed, _pinPage, &EnterPinWidget::onCancel);

	connect(this, &ATMInterface::digitPressed, _cardPage, &EnterCardWidget::onDigit);
	connect(this, &ATMInterface::enterPressed, _cardPage, &EnterCardWidget::onEnter);
	connect(this, &ATMInterface::clearPressed, _cardPage, &EnterCardWidget::onClear);
	connect(this, &ATMInterface::cancelPressed, _cardPage, &EnterCardWidget::onCancel);
}

void ATMInterface::on_btn0_clicked() { emit digitPressed(0); }
void ATMInterface::on_btn1_clicked() { emit digitPressed(1); }
void ATMInterface::on_btn2_clicked() { emit digitPressed(2); }
void ATMInterface::on_btn3_clicked() { emit digitPressed(3); }
void ATMInterface::on_btn4_clicked() { emit digitPressed(4); }
void ATMInterface::on_btn5_clicked() { emit digitPressed(5); }
void ATMInterface::on_btn6_clicked() { emit digitPressed(6); }
void ATMInterface::on_btn7_clicked() { emit digitPressed(7); }
void ATMInterface::on_btn8_clicked() { emit digitPressed(8); }
void ATMInterface::on_btn9_clicked() { emit digitPressed(9); }

void ATMInterface::on_btnEnter_clicked() { emit enterPressed(); }
void ATMInterface::on_btnClear_clicked() { emit clearPressed(); }
void ATMInterface::on_btnCancel_clicked() { emit cancelPressed(); }

void ATMInterface::on_btnLeft1_clicked() { emit sidePressed(false, 1); }
void ATMInterface::on_btnLeft2_clicked() { emit sidePressed(false, 2); }
void ATMInterface::on_btnLeft3_clicked() { emit sidePressed(false, 3); }
void ATMInterface::on_btnRight1_clicked() { emit sidePressed(true, 1); }
void ATMInterface::on_btnRight2_clicked() { emit sidePressed(true, 2); }
void ATMInterface::on_btnRight3_clicked() { emit sidePressed(true, 3); }