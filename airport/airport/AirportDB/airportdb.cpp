#include "airportdb.h"

#include <QFile>
#include <exception>

AirportDB::AirportDB(const QString& a_dbFileName): m_dbFileName(a_dbFileName)
{
    std::ifstream in(m_dbFileName.toStdString());

    m_size = 0;

    Flight tmp;

    // считаем количество записей в файле
    while (in >> tmp)
    {
        ++m_size;
    }
}

void AirportDB::add(const Flight &f)
{
    // открывайем файл с тегом добавления в конец
    std::ofstream out(m_dbFileName.toStdString(), std::ios::app);

    // добавляем новый файл
    out << f << '\n';

    // прибавляем размер
    ++m_size;
}

void AirportDB::addByIndex(const Flight &f, const qint64 &index)
{
    // если индекс равен размеру, добавляем в конец
    if(index == m_size)
    {
        add(f);
        return;
    }

    // выход за границы
    if (index > m_size || index < 0)
    {
        throw std::exception();
    }

    int i = -1;

    Flight tmp;

    // оссновной файл
    std::fstream in(m_dbFileName.toStdString());

    // временный файл
    const std::string tmpFileName = "tmpFile";
    std::ofstream tmpFile(tmpFileName);

    while (!in.eof())
    {
        // считываем данные из основного файла
        in >> tmp;

        ++i;

        if (i == index)
        {
            // если дошли до нужного индекса, записываем новый рейсс
            tmpFile << f << '\n';
        }

        // записываем во временный
        tmpFile << tmp << '\n';
    }

    in.close();
    tmpFile.close();

    // удаляем основной файл
    std::remove(m_dbFileName.toStdString().c_str());
    // переименовываем временный файл
    std::rename(tmpFileName.c_str(), m_dbFileName.toStdString().c_str());
}

void AirportDB::erase(const Flight &f)
{
    Flight tmp;
    // индикатор удаления только одного рейса
    bool E = false;

    // основной файл
    std::fstream in(m_dbFileName.toStdString());

    // временный фалй
    const std::string tmpFileName = "tmpFile";
    std::ofstream tmpFile(tmpFileName);

    while (!in.eof())
    {
        // считываем рейс из основного
        in >> tmp;

        // если нашли нужный рейс и ещё не удаляли
        if (tmp == f && !E)
        {
            // уменьшаем размер
            --m_size;
            // обновляем тег
            E = true;
            // не записываем текущий рейс
            continue;
        }

        // записываем во временный
        tmpFile << tmp  << '\n';
    }

    in.close();
    tmpFile.close();

    // удаляем основной файл
    std::remove(m_dbFileName.toStdString().c_str());
    // переименовываем временный файл
    std::rename(tmpFileName.c_str(), m_dbFileName.toStdString().c_str());
}

void AirportDB::eraseByIndex(const qint64 &index)
{
    // если индекс слишком большой или меньше 0, ошибка
    if (index >= m_size || index < 0)
    {
        throw std::exception();
    }

    int i = -1;

    Flight tmp;

    // основной файл
    std::fstream in(m_dbFileName.toStdString());

    // временный файл
    const std::string tmpFileName = "tmpFile";
    std::ofstream tmpFile(tmpFileName);

    while (!in.eof())
    {
        // считываем рейс из основного файла
        in >> tmp;

        ++i;

        // если дошли до нужного индекса пропускаем его
        if (i == index)
        {
            continue;
        }

        // записываем во временный
        tmpFile << tmp  << '\n';
    }

    in.close();
    tmpFile.close();

    // удаляем основной файл
    std::remove(m_dbFileName.toStdString().c_str());
    // переименовываем временный файл
    std::rename(tmpFileName.c_str(), m_dbFileName.toStdString().c_str());
}

void AirportDB::replace(const Flight &f, const qint64 &index)
{
    // если индекс слишком большой или меньше 0, ошибка
    if (index >= m_size || index < 0)
    {
        throw std::exception();
    }

    int i = -1;

    Flight tmp;

    // основной файл
    std::fstream in(m_dbFileName.toStdString());

    // временный файл
    const std::string tmpFileName = "tmpFile";
    std::ofstream tmpFile(tmpFileName);

    while (!in.eof())
    {
        // считываем даннные из временного файла
        in >> tmp;

        ++i;

        // если инашли нужный индекс
        if (i == index)
        {
            // записываем переданный рейс, и пропусскаем
            tmpFile << f << '\n';
            continue;
        }

        tmpFile << tmp << '\n';
    }

    in.close();
    tmpFile.close();

    // удаляем основной файл
    std::remove(m_dbFileName.toStdString().c_str());
    // переименовываем временный файл
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

        // если нашли запись с таким же номером рейса, возвращаем индекс
        if (tmp.flightNumber() == FlightNumbers)
        {
            return i;
        }
    }

    // если не нашли возвращем -1
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
    // переименовываем файл
    m_dbFileName = file;

    // открываем новый файл
    std::ifstream in(m_dbFileName.toStdString());

    m_size = 0;

    Flight tmp;

    // считаем количество записей в файле
    while (in >> tmp)
    {
        ++m_size;
    }
}

Flight AirportDB::operator[](const qint64 &index)
{
    // если индекс выходи за границы, ошибка
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

        // если дошли до нужного индекса
        // выходим из цикла
        if (i == index)
        {
            break;
        }
    }

    // возвращаем найденную запись
    return tmp;
}

