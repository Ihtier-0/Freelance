#include "airportdb.h"

#include <QFile>
#include <exception>

AirportDB::AirportDB(const QString& a_dbFileName): m_dbFileName(a_dbFileName)
{
    std::ifstream in(m_dbFileName.toStdString());

    m_size = 0;

    Flight tmp;

    while (in >> tmp)
    {
        ++m_size;
    }
}

void AirportDB::add(const Flight &f)
{
    std::ofstream out(m_dbFileName.toStdString(), std::ios::app);

    out << f << '\n';

    ++m_size;
}

void AirportDB::addByIndex(const Flight &f, const qint64 &index)
{
    if (index >= m_size || index < 0)
    {
        throw std::exception();
    }

    int i = -1;

    Flight tmp;

    std::fstream in(m_dbFileName.toStdString());

    const std::string tmpFileName = "tmpFile";
    std::ofstream tmpFile(tmpFileName);

    while (!in.eof())
    {
        in >> tmp;

        ++i;

        if (i == index)
        {
            tmpFile << f << '\n';
        }

        tmpFile << tmp << '\n';
    }

    in.close();
    tmpFile.close();

    std::remove(m_dbFileName.toStdString().c_str());
    std::rename(tmpFileName.c_str(), m_dbFileName.toStdString().c_str());
}

void AirportDB::erase(const Flight &f)
{
    Flight tmp;
    bool E = false;

    std::fstream in(m_dbFileName.toStdString());

    const std::string tmpFileName = "tmpFile";
    std::ofstream tmpFile(tmpFileName);

    while (!in.eof())
    {
        in >> tmp;

        if (tmp == f && !E)
        {
            --m_size;
            E = true;
            continue;
        }

        tmpFile << tmp  << '\n';
    }

    in.close();
    tmpFile.close();

    std::remove(m_dbFileName.toStdString().c_str());
    std::rename(tmpFileName.c_str(), m_dbFileName.toStdString().c_str());
}

void AirportDB::eraseByIndex(const qint64 &index)
{
    if (index >= m_size || index < 0)
    {
        throw std::exception();
    }

    int i = -1;

    Flight tmp;

    std::fstream in(m_dbFileName.toStdString());

    const std::string tmpFileName = "tmpFile";
    std::ofstream tmpFile(tmpFileName);

    while (!in.eof())
    {
        in >> tmp;

        ++i;

        if (i == index)
        {
            continue;
        }

        tmpFile << tmp  << '\n';
    }

    in.close();
    tmpFile.close();

    std::remove(m_dbFileName.toStdString().c_str());
    std::rename(tmpFileName.c_str(), m_dbFileName.toStdString().c_str());
}

void AirportDB::replace(const Flight &f, const qint64 &index)
{
    if (index >= m_size || index < 0)
    {
        throw std::exception();
    }

    int i = -1;

    Flight tmp;

    std::fstream in(m_dbFileName.toStdString());

    const std::string tmpFileName = "tmpFile";
    std::ofstream tmpFile(tmpFileName);

    while (!in.eof())
    {
        in >> tmp;

        ++i;

        if (i == index)
        {
            tmpFile << f << '\n';
            continue;
        }

        tmpFile << tmp << '\n';
    }

    in.close();
    tmpFile.close();

    std::remove(m_dbFileName.toStdString().c_str());
    std::rename(tmpFileName.c_str(), m_dbFileName.toStdString().c_str());
}

int AirportDB::findIndex(const qint64 &FlightNumbers)
{
    int i = -1;

    Flight tmp;

    std::fstream in(m_dbFileName.toStdString());

    while (!in.eof())
    {
        in >> tmp;

        ++i;

        if (tmp.flightNumber() == FlightNumbers)
        {
            return i;
        }
    }

    return -1;
}

qint64 AirportDB::size()
{
    return m_size;
}

QString AirportDB::getDBFileAddress()
{
    return m_dbFileName;
}

void AirportDB::openFile(const QString &file)
{
    m_dbFileName = file;

    std::ifstream in(m_dbFileName.toStdString());

    m_size = 0;

    Flight tmp;

    while (in >> tmp)
    {
        ++m_size;
    }
}

Flight AirportDB::operator[](const qint64 &index)
{
    if (index >= m_size || index < 0)
    {
        throw std::exception();
    }

    int i = -1;

    Flight tmp;

    std::fstream in(m_dbFileName.toStdString());

    while (!in.eof())
    {
        in >> tmp;

        ++i;

        if (i == index)
        {
            break;
        }
    }

    return tmp;
}

