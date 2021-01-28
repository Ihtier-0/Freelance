#include "mainwindow.h"
#include <QApplication>
#include <QDateTime>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    airportTable t("db");
    MainWindow w(&t);

//    Flight tmp1(1, "USA", QDateTime(QDate(2000, 7, 1), QTime(10, 30)), QDateTime(QDate(2000, 7, 2), QTime(10, 30)), 9);
//    Flight tmp2(2, "China", QDateTime(QDate(2000, 7, 6), QTime(20, 30)), QDateTime(QDate(2000, 7, 7), QTime(10, 30)), 100);
//    Flight tmp3(5, "Russia", QDateTime(QDate(2000, 7, 8), QTime(1, 30)), QDateTime(QDate(2000, 7, 9), QTime(10, 30)), 25);
//    Flight tmp4(12, "USA", QDateTime(QDate(2000, 7, 8), QTime(10, 45)), QDateTime(QDate(2000, 7, 9), QTime(10, 30)), 27);
//    Flight tmp5(25, "France", QDateTime(QDate(2000, 7, 9), QTime(15, 49)), QDateTime(QDate(2000, 7, 10), QTime(10, 30)), 9);
//    Flight tmp7(29, "USA", QDateTime(QDate(2000, 7, 11), QTime(00, 30)), QDateTime(QDate(2000, 7, 12), QTime(10, 30)), 9);
//    Flight tmp8(30, "Japan", QDateTime(QDate(2000, 7, 12), QTime(5, 30)), QDateTime(QDate(2000, 7, 13), QTime(10, 30)), 0);
//    Flight tmp9(40, "Korea", QDateTime(QDate(2000, 7, 15), QTime(3, 30)), QDateTime(QDate(2000, 7, 16), QTime(10, 30)), 60);
//    Flight tmp10(50, "USA", QDateTime(QDate(2000, 7, 25), QTime(2, 30)), QDateTime(QDate(2000, 7, 26), QTime(10, 30)), 9);

//    const QString tmpFileName = "db";
//    std::ofstream tmpFile(tmpFileName.toStdString());

//    tmpFile.write((char*)&tmp1,sizeof(Flight));
//    tmpFile.write((char*)&tmp2,sizeof(Flight));
//    tmpFile.write((char*)&tmp3,sizeof(Flight));
//    tmpFile.write((char*)&tmp4,sizeof(Flight));
//    tmpFile.write((char*)&tmp5,sizeof(Flight));
//    tmpFile.write((char*)&tmp7,sizeof(Flight));
//    tmpFile.write((char*)&tmp8,sizeof(Flight));
//    tmpFile.write((char*)&tmp9,sizeof(Flight));
//    tmpFile.write((char*)&tmp10,sizeof(Flight));

//    tmpFile.close();

//    std::ifstream tmpFilei(tmpFileName.toStdString());

//    if(tmpFilei.is_open())
//    {
//        qDebug() << "open";
//    }

//    Flight tmp;

//    while(tmpFilei.read((char*)&tmp,sizeof(Flight)))
//    {
//        qDebug() << tmp.toQString() << '\n';
//    }

//    qDebug() << "end";

    w.show();
    return a.exec();
}
