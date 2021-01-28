#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AirportTable/airportTable.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(airportTable *a_table, QWidget *parent = nullptr);
    ~MainWindow();

private:
    airportTable *m_table;
};
#endif // MAINWINDOW_H
