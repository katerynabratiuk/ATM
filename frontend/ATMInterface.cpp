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

	connect(this, &ATMInterface::digitPressed, this, &ATMInterface::forwardDigit);
	connect(this, &ATMInterface::enterPressed, this, &ATMInterface::forwardEnter);
	connect(this, &ATMInterface::clearPressed, this, &ATMInterface::forwardClear);
	connect(this, &ATMInterface::cancelPressed, this, &ATMInterface::forwardCancel);
	connect(this, &ATMInterface::sideButtonPressed, this, &ATMInterface::forwardSideButton);
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

void ATMInterface::on_btnLeft1_clicked() { emit sideButtonPressed(false, 1); }
void ATMInterface::on_btnLeft2_clicked() { emit sideButtonPressed(false, 2); }
void ATMInterface::on_btnLeft3_clicked() { emit sideButtonPressed(false, 3); }
void ATMInterface::on_btnRight1_clicked() { emit sideButtonPressed(true, 1); }
void ATMInterface::on_btnRight2_clicked() { emit sideButtonPressed(true, 2); }
void ATMInterface::on_btnRight3_clicked() { emit sideButtonPressed(true, 3); }

void ATMInterface::forwardDigit(int digit) 
{
	qobject_cast<IPage*>(_ui.widgetStack->currentWidget())->onDigit(digit);
}

void ATMInterface::forwardEnter() 
{
	qobject_cast<IPage*>(_ui.widgetStack->currentWidget())->onEnter();
}

void ATMInterface::forwardClear() 
{
	qobject_cast<IPage*>(_ui.widgetStack->currentWidget())->onClear();
}

void ATMInterface::forwardCancel() 
{
	qobject_cast<IPage*>(_ui.widgetStack->currentWidget())->onCancel();
}

void ATMInterface::forwardSideButton(bool rightSide, int index)
{
	qobject_cast<IPage*>(_ui.widgetStack->currentWidget())->onSideButton(rightSide, index);
}