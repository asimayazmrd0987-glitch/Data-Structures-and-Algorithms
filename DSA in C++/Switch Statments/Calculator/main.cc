#include <QApplication>
#include "calculatorwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CalculatorWindow window;
    window.show();

    return app.exec();
}