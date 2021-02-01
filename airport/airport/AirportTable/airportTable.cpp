#include "airportTable.h"
#include "AirportDB/airportdb.h"

#include <QHeaderView>
#include <QDebug>

airportTable::airportTable(QString a_dbFileName) : m_db(a_dbFileName)
{
    this->setColumnCount(5);
    this->setHorizontalHeaderLabels(QStringList() << "flight number" << "destination"
                                                        << "departureTime" << "arrival time"
                                                        << "number free seats in cabin");
    this->Update();
}


void airportTable::openFile(const QString &file)
{
    m_db.openFile(file);

    this->Update();
}

void airportTable::Update()
{
    m_size = m_db.size();
    this->setRowCount(m_db.size());
    Flight tmp;
    for(qint64 i = 0; i < m_db.size(); ++i)
    {
        tmp = m_db[i];

        this->setItem(i, 0, new QTableWidgetItem(QString::number(tmp.flightNumber())));
        this->setItem(i, 1, new QTableWidgetItem(tmp.destination()));
        this->setItem(i, 2, new QTableWidgetItem(tmp.departureTime().toString()));
        this->setItem(i, 3, new QTableWidgetItem(tmp.arrivalTime().toString()));
        this->setItem(i, 4, new QTableWidgetItem(QString::number(tmp.numberFreeSeatsInCabin())));
    }

    this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(int i = 0; i < 5; ++i)
    {
        this->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
}

void airportTable::add(const Flight &f)
{
    m_db.add(f);

    this->insertRow(m_size);
    this->setItem(m_size, 0, new QTableWidgetItem(QString::number(f.flightNumber())));
    this->setItem(m_size, 1, new QTableWidgetItem(f.destination()));
    this->setItem(m_size, 2, new QTableWidgetItem(f.departureTime().toString()));
    this->setItem(m_size, 3, new QTableWidgetItem(f.arrivalTime().toString()));
    this->setItem(m_size, 4, new QTableWidgetItem(QString::number(f.numberFreeSeatsInCabin())));
    ++m_size;
}

void airportTable::save(const QString &file)
{
    std::ofstream out(file.toStdString());

    for(int i = 0; i < m_size; ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            out << this->item(i,j)->data(Qt::DisplayRole).toString().toStdString() << ' ';
        }
        out << '\n';
    }
}

void airportTable::updateNumberFreeSeatsInCabin(const quint64 &FlightNumbers, const quint64 &newNumberOfFreeSeatsInTheCabin)
{
    int index = m_db.findIndex(FlightNumbers);

    if(index != -1)
    {
        Flight tmp = m_db[index];
        qDebug() << tmp.toQString();
        m_db.replace(Flight(tmp.flightNumber(), tmp.destination(), tmp.departureTime(), tmp.arrivalTime(),
                            newNumberOfFreeSeatsInTheCabin), index);
    }

    Update();
}

QString airportTable::getDBFileAddress()
{
    return m_db.getDBFileAddress();
}

void airportTable::eraseIf(std::function<bool (const Flight &)> f)
{
    Update();

    int del = 0;

    for(int i = 0; i < m_db.size(); ++i)
    {
        if(f(m_db[i]))
        {
            m_size--;
            this->removeRow(i - del);
            del++;
        }
    }
}
