#include "ATMInterface.h"

ATMInterface::ATMInterface(QWidget *parent, ICardController* cardController)
	: QMainWindow(parent), _cardController(cardController)
{
    _ui.setupUi(this);
    addPages();
    connectSlots();

	changeCurrentPage(Pages::LoginPage);
}

ATMInterface::~ATMInterface()
{}

void ATMInterface::changeCurrentPage(Pages page)
{
    _ui.widgetStack->setCurrentIndex(static_cast<int>(page));
}

void ATMInterface::addPages()
{
    _ui.widgetStack->insertWidget(static_cast<int>(Pages::LoginPage), &_loginPage);
}

void ATMInterface::connectSlots()
{
    connect(&_loginPage, &LoginWidget::changePage, this, &ATMInterface::changeCurrentPage);
}

