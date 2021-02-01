#include "mainwindow.h"
#include <QApplication>
#include <QDateTime>
#include <iostream>
#include <QDir>

#include "Flight/flight.h"
#include "AirportDB/airportdb.h"
#include <fstream>

#include <QDebug>

int main(int argc, char *argv[])
{

/*
        Flight tmp1(1, "USA", QDateTime(QDate(2000, 1, 1), QTime(10, 30)), QDateTime(QDate(2000, 1, 2), QTime(10, 30)), 9);
        Flight tmp2(2, "China", QDateTime(QDate(2000, 2, 6), QTime(20, 30)), QDateTime(QDate(2000, 2, 7), QTime(10, 30)), 100);
        Flight tmp3(5, "Russia", QDateTime(QDate(2000, 3, 8), QTime(1, 30)), QDateTime(QDate(2000, 3, 9), QTime(10, 30)), 25);
        Flight tmp4(12, "USA", QDateTime(QDate(2000, 4, 8), QTime(10, 45)), QDateTime(QDate(2000, 4, 9), QTime(10, 30)), 27);
        Flight tmp5(25, "France", QDateTime(QDate(2000, 5, 9), QTime(15, 49)), QDateTime(QDate(2000, 5, 10), QTime(10, 30)), 9);
        Flight tmp6(29, "USA", QDateTime(QDate(2000, 6, 11), QTime(00, 30)), QDateTime(QDate(2000, 6, 12), QTime(10, 30)), 9);
        Flight tmp7(30, "Japan", QDateTime(QDate(2000, 7, 12), QTime(5, 30)), QDateTime(QDate(2000, 7, 13), QTime(10, 30)), 0);
        Flight tmp8(40, "Korea", QDateTime(QDate(2000, 8, 15), QTime(3, 30)), QDateTime(QDate(2000, 8, 16), QTime(10, 30)), 60);
        Flight tmp9(50, "USA", QDateTime(QDate(2000, 9, 25), QTime(2, 30)), QDateTime(QDate(2000, 9, 26), QTime(10, 30)), 9);
        Flight tmp0(60, "USA", QDateTime(QDate(2000, 10, 25), QTime(2, 30)), QDateTime(QDate(2000, 10, 26), QTime(10, 30)), 9);
        Flight tmp10(70, "USA", QDateTime(QDate(2000, 11, 25), QTime(2, 30)), QDateTime(QDate(2000, 11, 26), QTime(10, 30)), 9);
        Flight tmp11(80, "USA", QDateTime(QDate(2000, 12, 25), QTime(2, 30)), QDateTime(QDate(2000, 12, 26), QTime(10, 30)), 9);
        const QString tmpFileName = "db";
        std::ofstream tmpFile(tmpFileName.toStdString().c_str());
        tmpFile << tmp1 << '\n';
        tmpFile << tmp2 << '\n';
        tmpFile << tmp3 << '\n';
        tmpFile << tmp4 << '\n';
        tmpFile << tmp5 << '\n';
        tmpFile << tmp6 << '\n';
        tmpFile << tmp7 << '\n';
        tmpFile << tmp8 << '\n';
        tmpFile << tmp9 << '\n';
        tmpFile << tmp0 << '\n';
        tmpFile << tmp10 << '\n';
        tmpFile << tmp11 << '\n';
        tmpFile.close();
        AirportDB db("db");
        Flight tmp;
        std::cout << '\n';
        for (qint64 i = 0; i < db.size(); ++i)
        {
            tmp = db[i];
            qDebug() << tmp.toQString();
        }
*/

    QApplication a(argc, argv);
    airportTable t;
    MainWindow w(&t);

    w.show();
    return a.exec();
}
