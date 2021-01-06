#include "partsDatabase.h"
#include "utils.h"

unsigned int partsDatabase::size()
{
    return m_table.size();
}

unsigned int partsDatabase::countParts(const part& type)
{
    unsigned int result = 0, size = m_table.size();

    for (unsigned int i = 0; i < size; ++i)
    {
        if (m_table[i].get_type() == type.get_type())
        {
            ++result;
        }
    }

    return result;
}

void partsDatabase::addPart(const part& type)
{
    m_table.push_back(type);
}

void partsDatabase::removePart(const part& type)
{
    unsigned int size = m_table.size();

    for (unsigned int i = 0; i < size; ++i)
    {
        if (m_table[i].get_type() == type.get_type())
        {
            m_table.erase(m_table.begin() + i);
            return;
        }
    }
}

std::istream& operator>>(std::istream& is, partsDatabase& db)
{
    partType tmp;
    while (!is.eof())
    {
        is >> tmp;
        db.m_table.push_back(partTypeToPart(tmp));
    }

    return is;
}
