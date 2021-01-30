#include "binaryAirportDB.h"

#include <QFile>

binaryAirportDB::binaryAirportDB(const QString& a_dbFileName): m_dbFileName(a_dbFileName)
{
    std::fstream openTest(m_dbFileName.toStdString());

    m_size = 0;

    Flight tmp;

    while (!openTest.eof())
    {
        openTest.read((char*)&tmp, sizeof(Flight));
        std::cout << tmp << '\n';
        ++m_size;
    }
    openTest.close();
}

void binaryAirportDB::add(const Flight &f)
{
    std::ofstream out(m_dbFileName.toStdString(), std::ios::app);

    out.write((char*)&f, sizeof(Flight));

    ++m_size;
}

void binaryAirportDB::addByIndex(const Flight &f, const qint64 &index)
{
    if (index >= m_size || index < 0)
    {
        throw std::exception("out of range!");
    }

    int i = -1;

    Flight tmp;

    std::fstream in(m_dbFileName.toStdString());

    const std::string tmpFileName = "tmpFile";
    std::ofstream tmpFile(tmpFileName);

    while (!in.eof())
    {
        in.read((char*)&tmp, sizeof(Flight));

        ++i;

        if (i == index)
        {
            tmpFile.write((char*)&f, sizeof(f));
        }

        tmpFile.write((char*)&tmp, sizeof(tmp));
    }

    in.close();
    tmpFile.close();

    std::remove(m_dbFileName.toStdString().c_str());
    std::rename(tmpFileName.c_str(), m_dbFileName.toStdString().c_str());
}

void binaryAirportDB::erase(const Flight &f)
{
    Flight tmp;
    bool E = false;

    std::fstream in(m_dbFileName.toStdString());

    const std::string tmpFileName = "tmpFile";
    std::ofstream tmpFile(tmpFileName);

    while (!in.eof())
    {
        in.read((char*)&tmp, sizeof(Flight));

        if (tmp == f && !E)
        {
            --m_size;
            E = true;
            continue;
        }

        tmpFile.write((char*)&tmp, sizeof(tmp));
    }

    in.close();
    tmpFile.close();

    std::remove(m_dbFileName.toStdString().c_str());
    std::rename(tmpFileName.c_str(), m_dbFileName.toStdString().c_str());
}

void binaryAirportDB::eraseByIndex(const qint64 &index)
{
    if (index >= m_size || index < 0)
    {
        throw std::exception("out of range!");
    }

    int i = -1;

    Flight tmp;

    std::fstream in(m_dbFileName.toStdString());

    const std::string tmpFileName = "tmpFile";
    std::ofstream tmpFile(tmpFileName);

    while (!in.eof())
    {
        in.read((char*)&tmp, sizeof(Flight));

        ++i;

        if (i == index)
        {
            continue;
        }

        tmpFile.write((char*)&tmp, sizeof(tmp));
    }

    in.close();
    tmpFile.close();

    std::remove(m_dbFileName.toStdString().c_str());
    std::rename(tmpFileName.c_str(), m_dbFileName.toStdString().c_str());
}

void binaryAirportDB::replace(const Flight &f, const qint64 &index)
{
    if (index >= m_size || index < 0)
    {
        throw std::exception("out of range!");
    }

    std::fstream in(m_dbFileName.toStdString());

    in.seekg(sizeof(Flight) * index, std::ios::beg);


    in.write((char*)&f, sizeof(Flight));
}

qint64 binaryAirportDB::size()
{
    return m_size;
}

Flight binaryAirportDB::operator[](const qint64 &index)
{
    if (index >= m_size || index < 0)
    {
        throw std::exception("out of range!");
    }

    std::fstream in(m_dbFileName.toStdString());
    Flight tmp;
    in.seekg(sizeof(tmp) * static_cast<unsigned int>(index), std::ios::beg);

    in.read((char*)&tmp, sizeof(Flight));

    return tmp;
}

