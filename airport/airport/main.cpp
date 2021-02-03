#include "mainwindow.h"
#include <QApplication>
#include <QDateTime>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    airportTable t;
    MainWindow w(&t);
    w.show();
    return a.exec();
}
