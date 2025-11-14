#include "frontend/ATMInterface.h"
#include <QtWidgets/QApplication>

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
    PostgresDBConnection c(
        "atm", "postgres", "127.0.0.1", 5432, "atm_pass"
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
