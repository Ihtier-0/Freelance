#ifndef AIRPORTTABLE_H
#define AIRPORTTABLE_H

#include <QTableWidget>
#include "BinaryAirportDB/binaryAirportDB.h"

class airportTable : public QTableWidget
{
    Q_OBJECT
public:
    airportTable(QString a_dbFileName);
private:
    binaryAirportDB m_db;
};

#endif // AIRPORTTABLE_H
