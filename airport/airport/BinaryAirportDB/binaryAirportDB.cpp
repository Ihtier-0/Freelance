#include "binaryAirportDB.h"

#include <QFile>

binaryAirportDB::binaryAirportDB(const QString& a_dbFileName): m_dbFileName(a_dbFileName)
{
    std::fstream openTest(m_dbFileName.toStdString());

      m_size = 0;

     Flight tmp;

    while(openTest.read((char*)&tmp,sizeof(tmp)))
    {
          ++m_size;
    }

    openTest.clear();
    openTest.close();
}

void binaryAirportDB::add(const Flight &f)
{
    std::ofstream out(m_dbFileName.toStdString(), std::ios::app);

    out.write((char*)&f,sizeof(f));

    ++m_size;
}

void binaryAirportDB::erase(const Flight &f)
{

    Flight tmp;

    std::fstream in(m_dbFileName.toStdString());

    const QString tmpFileName = "tmpFile";
    std::fstream tmpFile(tmpFileName.toStdString());

    while(!in.eof())
    {
        in.read((char*)&tmp,sizeof(tmp));

        if(tmp == f)
        {
            continue;
            --m_size;
        }

        tmpFile.write((char*)&tmp,sizeof(tmp));
    }

    QFile::remove(m_dbFileName);
    QFile::rename(tmpFileName, m_dbFileName);
}

void binaryAirportDB::erase(const qint64 &index)
{
    qint64 i = -1;

    Flight tmp;

    std::fstream in(m_dbFileName.toStdString());

    const QString tmpFileName = "tmpFile";
    std::fstream tmpFile(tmpFileName.toStdString());

    while(!in.eof())
    {
        in.read((char*)&tmp,sizeof(tmp));
        ++i;

        if(i == index)
        {
            continue;
            --m_size;
        }

        tmpFile.write((char*)&tmp,sizeof(tmp));
    }

    QFile::remove(m_dbFileName);
    QFile::rename(tmpFileName, m_dbFileName);
}

void binaryAirportDB::replace(const Flight &f, const qint64 &index)
{
    qint64 i = -1;

    Flight tmp;

    std::fstream in(m_dbFileName.toStdString());

    const QString tmpFileName = "tmpFile";
    std::fstream tmpFile(tmpFileName.toStdString());

    while(!in.eof())
    {
        in.read((char*)&tmp,sizeof(tmp));
        ++i;

        if(i == index)
        {
            tmpFile.write((char*)&f,sizeof(f));
        }
        else
        {
            tmpFile.write((char*)&tmp,sizeof(tmp));
        }
    }

    QFile::remove(m_dbFileName);
    QFile::rename(tmpFileName, m_dbFileName);
}

quint64 binaryAirportDB::size()
{
    return m_size;
}

Flight binaryAirportDB::operator[](const quint64 &index)
{
    if(index >= m_size)
    {
        throw std::exception("out of range!");
    }

    std::fstream in(m_dbFileName.toStdString());
    Flight tmp;
    in.seekg(sizeof(tmp) * index, std::ios::beg);

    in.read((char*)&tmp,sizeof(tmp));

    return tmp;
}

