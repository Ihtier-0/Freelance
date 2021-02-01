#ifndef AIRPORTTABLE_H
#define AIRPORTTABLE_H

#include <QTableWidget>
#include "AirportDB/airportdb.h"

class airportTable : public QTableWidget
{
    Q_OBJECT
public:
    airportTable(QString a_dbFileName = "");
    void openFile(const QString& file);
    void add(const Flight& f);
    void save(const QString& file);
    void updateNumberFreeSeatsInCabin(const quint64 &FlightNumbers, const quint64 &newNumberOfFreeSeatsInTheCabin);
    QString getDBFileAddress();
    void eraseIf(std::function<bool(const Flight&)> f);
private:
    void Update();
    int m_size;
    AirportDB m_db;
};

#endif // AIRPORTTABLE_H
