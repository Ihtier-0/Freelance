#include "airportTable.h"

//// номер рейса
//qint64 m_flightNumber;
//// пункт назначения
//QString m_destination;
//// время вылета
//QDateTime m_departureTime;
//// время прибытия
//QDateTime m_arrivalTime;
//// количество свободных мест в салоне
//qint64 m_numberFreeSeatsInCabin;

airportTable::airportTable(const QString &a_dbFileName) : m_DB(a_dbFileName)
{
    quint64 size = m_DB.size();

    this->setRowCount(size);
    this->setColumnCount(5);

    this->setHorizontalHeaderLabels(QStringList() << "flight number" << "destination"
                                                    << "departureTime" << "arrival time"
                                                    << "number free seats in cabin");
    Flight tmp;
    for(quint64 i = 0; i < size; ++i)
    {
        tmp = m_DB[i];

        this->setItem(i, 0, new QTableWidgetItem(QString::number(tmp.flightNumber())));
        this->setItem(i, 1, new QTableWidgetItem(tmp.destination()));
        this->setItem(i, 2, new QTableWidgetItem(tmp.departureTime().toString()));
        this->setItem(i, 3, new QTableWidgetItem(tmp.arrivalTime().toString()));
        this->setItem(i, 4, new QTableWidgetItem(QString::number(tmp.numberFreeSeatsInCabin())));
    }
}
