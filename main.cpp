#define LOGGING_LEVEL_1

#include "mainwindow.h"
#include <QApplication>
#include "logger/logger.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    LOG("Starting the application..");
    return a.exec();
}
