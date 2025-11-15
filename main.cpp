#include "frontend/ATMInterface.h"
#include <QtWidgets/QApplication>
#include <filesystem>
#include <iostream>
#include "backend/external/dotenv.h"

int main(int argc, char *argv[])
{
    dotenv::init("../../.env");

    if (const char* db_name = std::getenv("DB_NAME")) {
        std::cout << "DB_NAME=" << db_name << std::endl;
    }
    else {
        std::cerr << "DB_NAME is not set!" << std::endl;
    }

    QApplication app(argc, argv);
    ATMInterface window;
    window.show();
    return app.exec();
}
