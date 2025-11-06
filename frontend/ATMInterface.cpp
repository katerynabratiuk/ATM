#include "frontend/ATMInterface.h"

ATMInterface::ATMInterface(/*ICardController& cardController, */QWidget *parent)
	: QMainWindow(parent)/*, _cardController(cardController)*/
{
    _ui.setupUi(this);
    addPages();
    connectSlots();

	changeCurrentPage(Pages::StartingPage);
}

ATMInterface::~ATMInterface()
{}

void ATMInterface::changeCurrentPage(Pages page)
{
    _ui.widgetStack->setCurrentIndex(static_cast<int>(page));
}

void ATMInterface::addPages()
{
    _ui.widgetStack->insertWidget(static_cast<int>(Pages::StartingPage), &_startPage);
    _ui.widgetStack->insertWidget(static_cast<int>(Pages::LoginPage), &_loginPage);
    _ui.widgetStack->insertWidget(static_cast<int>(Pages::MainMenuPage), &_mainMenuPage);
}

void ATMInterface::connectSlots()
{
    connect(&_loginPage, &LoginWidget::changePage, this, &ATMInterface::changeCurrentPage);
    connect(&_startPage, &StartWidget::changePage, this, &ATMInterface::changeCurrentPage);
    connect(&_mainMenuPage, &MainMenuWidget::changePage, this, &ATMInterface::changeCurrentPage);
}

