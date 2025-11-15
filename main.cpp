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

    if (const char* db_name = std::getenv("DB_NAME")) {
        std::cout << "DB_NAME=" << db_name << std::endl;
    }
    else {
        std::cerr << "DB_NAME is not set!" << std::endl;
    }

    PostgresDBConnection c(
        "atm", "postgres", "127.0.0.1", 5432, "aa1010AA"
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
