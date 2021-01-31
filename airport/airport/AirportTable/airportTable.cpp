#include "airportTable.h"
#include "BinaryAirportDB/binaryAirportDB.h"

airportTable::airportTable(QString a_dbFileName) : m_db(a_dbFileName)
{
    this->setColumnCount(5);
    this->setRowCount(m_db.size());
    this->setHorizontalHeaderLabels(QStringList() << "flight number" << "destination"
                                                        << "departureTime" << "arrival time"
                                                        << "number free seats in cabin");
    Flight *tmp;
    for(qint64 i = 0; i < m_db.size(); ++i)
    {
        *tmp = m_db[i];

        this->setItem(i, 0, new QTableWidgetItem(QString::number(tmp->flightNumber())));
        this->setItem(i, 1, new QTableWidgetItem(/*tmp.destination()*/));
        this->setItem(i, 2, new QTableWidgetItem(tmp->departureTime().toString()));
        this->setItem(i, 3, new QTableWidgetItem(tmp->arrivalTime().toString()));
        this->setItem(i, 4, new QTableWidgetItem(QString::number(tmp->numberFreeSeatsInCabin())));
    }
}
