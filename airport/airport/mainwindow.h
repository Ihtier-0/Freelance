#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AirportTable/airportTable.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(airportTable *a_table, QWidget *parent = nullptr);

private:
    airportTable *m_table;

public slots:
    void openFile();
    void saveTable();
    void add();
    void flightsToTheEnteredDestinationWithFreeSeats();
    void deleteAllRecordsWithSpecificFlightNumbers();
    void updateTheNumberOfFreeSeatsInTheCabinInTheSpecifiedFlightNumber();
};
#endif // MAINWINDOW_H
