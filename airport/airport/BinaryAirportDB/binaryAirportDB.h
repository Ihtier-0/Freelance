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

    void erase(const Flight& f);
    void erase(const qint64& index);

    void replace(const Flight& f, const qint64& index);

    quint64 size();

    Flight operator[](const quint64& index);
private:
    QString m_dbFileName;
    quint64 m_size;
};

#endif // FLIGHT_H
