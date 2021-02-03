#ifndef BINARYDB_H
#define BINARYDB_H

#include <fstream>
#include <QString>

#include "Flight/flight.h"

#include <functional>

// класс который взаимодействет с файлом содержащим данные о рейсах
class AirportDB
{
public:
    // конструктор который принимает имя файла
    AirportDB(const QString& a_dbFileName);
    // конструктор по умолчанию
    AirportDB();

    // добавление рейса в файл
    void add(const Flight& f);
    // добавление рейся в файл по индексу
    void addByIndex(const Flight& f, const qint64& index);

    // удалить рейс f
    void erase(const Flight& f);
    // удалить рейс по индексу
    void eraseByIndex(const qint64& index);

    // заменить рейс под номером index на рейс f
    void replace(const Flight& f, const qint64& index);

    // найти индекс рейса с номером FlightNumbers
    int findIndex(const qint64 &FlightNumbers);

    // количество записей в файле
    qint64 size();
    // геттер названия файла
    QString getDBFileAddress();

    // заменить текущий файл на новый
    void openFile(const QString& file);

    // перегрузка оператора []
    Flight operator[](const qint64& index);

private:
    // имя файла
    QString m_dbFileName;
    // количество записей в ФАЙЛЕ
    qint64 m_size;
};

#endif // FLIGHT_H
