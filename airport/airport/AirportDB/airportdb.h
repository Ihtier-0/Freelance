#ifndef BINARYDB_H
#define BINARYDB_H

#include <fstream>
#include <QString>

#include "Flight/flight.h"

#include <functional>

class AirportDB
{
public:
    AirportDB(const QString& a_dbFileName);
    AirportDB();

    void add(const Flight& f);
    void addByIndex(const Flight& f, const qint64& index);

    void erase(const Flight& f);
    void eraseByIndex(const qint64& index);

    void replace(const Flight& f, const qint64& index);

    int findIndex(const qint64 &FlightNumbers);

    qint64 size();
    QString getDBFileAddress();

    void openFile(const QString& file);

    Flight operator[](const qint64& index);

private:
    QString m_dbFileName;
    qint64 m_size;
};

#endif // FLIGHT_H
