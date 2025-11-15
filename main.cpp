#include "frontend/ATMInterface.h"
#include <QtWidgets/QApplication>
#include <filesystem>
#include <iostream>
#include "backend/external/dotenv.h"

#include "backend/repositories/PostgresDBConnection.h" 
#include "backend/repositories/BanknoteRepository.h"
#include "backend/repositories/CardRepository.h"
#include "backend/repositories/TransactionRepository.h"

#include "backend/services/BanknoteService.h"
#include "backend/services/CardService.h"
#include "backend/services/TransactionService.h"

#include "backend/controllers/CardController.h"
#include "backend/controllers/TransactionController.h"

int main(int argc, char *argv[])
{
    dotenv::init("../../.env");

    PostgresDBConnection c(
        std::getenv("DB_NAME"),
        std::getenv("DB_USER"),
        std::getenv("DB_HOST"),
        std::atoi(std::getenv("DB_PORT")),
        std::getenv("DB_PASSWORD")
    );

    if (!c.connect()) 
    {
        throw std::runtime_error("DB: connect() returned false");
    }

    BanknoteRepository banknoteRepo(c, 1);
    TransactionRepository transactionRepo(c);
    CardRepository cardRepo(c);
     
    BanknoteService banknoteService(banknoteRepo);
    TransactionService transactionService(transactionRepo);
    CardService cardService(cardRepo, banknoteService, transactionRepo);

	TransactionController transactionController(transactionService);
	CardController cardController(cardService);

    QApplication app(argc, argv);
    ATMInterface window(cardController);
    window.show();
    return app.exec();
}
