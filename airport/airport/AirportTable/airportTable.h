#ifndef AIRPORTTABLE_H
#define AIRPORTTABLE_H

#include <QTableWidget>
#include "AirportDB/airportdb.h"

// класс который заполняет таблицу
class airportTable : public QTableWidget
{
    Q_OBJECT
public:
    // конструктор принимающий название файла
    airportTable(QString a_dbFileName = "");
    // открытие файла
    void openFile(const QString& file);
    // добавление рейса в таблицу
    void add(const Flight& f);
    // сохранить текущую таблицу в файл
    void save(const QString& file);
    // обновить количество свободных мест в номере рейса
    void updateNumberFreeSeatsInCabin(const quint64 &FlightNumbers, const quint64 &newNumberOfFreeSeatsInTheCabin);
    // получить адрес базы данных
    QString getDBFileAddress();
    // удалить из таблицы если не удовлетворяет условию f
    void eraseIf(std::function<bool(const Flight&)> f);
    // заполнение таблицы всеми данными из файла
    void Update();
private:
    // количество записей в ТАБЛИЦЕ
    int m_size;
    // база данных таблицы
    AirportDB m_db;
};

#endif // AIRPORTTABLE_H
