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
    // указатель на таблицу аэропорта
    airportTable *m_table;

public slots:
    // открыть файл
    void openFile();
    // сохранить таблицу в файл
    void saveTable();
    // добавить рейс в конец таблицы
    void add();
    // показатать рейсы летящие в введённое место у которого есть свободные места
    void flightsToTheEnteredDestinationWithFreeSeats();
    // удалить все записи с введённым номером рейса
    void deleteAllRecordsWithSpecificFlightNumbers();
    // обновить количество свободных мест в рейсе с введенным номером
    void updateTheNumberOfFreeSeatsInTheCabinInTheSpecifiedFlightNumber();
    // показ всего файла
    void clearFilters();
};

#endif // MAINWINDOW_H
