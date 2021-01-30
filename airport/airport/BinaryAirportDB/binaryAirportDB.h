#ifndef BINARYDB_H
#define BINARYDB_H

#include <fstream>
#include <QString>

#include "Flight/flight.h"

class binaryAirportDB
{
public:
    binaryAirportDB(const QString& a_dbFileName);

    void add(const Flight& f);
    void addByIndex(const Flight& f, const qint64& index);

    void erase(const Flight& f);
    void eraseByIndex(const qint64& index);

    void replace(const Flight& f, const qint64& index);

    qint64 size();

    Flight operator[](const qint64& index);

private:
    QString m_dbFileName;
    qint64 m_size;
};

#endif // FLIGHT_H
