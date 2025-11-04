#include "ATMSimulator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ATMSimulator window;
    window.show();
    return app.exec();
}
