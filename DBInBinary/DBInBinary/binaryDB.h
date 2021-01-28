#pragma once

#include <string>
#include <fstream>
#include <exception>
#include <cstdio>

template<class T>
class binaryDB
{
public:
    binaryDB(const std::string& a_dbFileName) : m_dbFileName(a_dbFileName)
    {
        std::fstream openTest(m_dbFileName);

        m_size = 0;

        T tmp;

        while (openTest.read((char*)&tmp, sizeof(T)))
        {
            ++m_size;
        }
    }

    // добавление строки
    void add(const T& f)
    {
        std::ofstream out(m_dbFileName, std::ios::app);

        out.write((char*)&f, sizeof(T));

        ++m_size;
    }

    void addByIndex(const T& f, const int& index)
    {
        if (index >= m_size || index < 0)
        {
            throw std::exception("out of range!");
        }

        int i = -1;

        T tmp;

        std::fstream in(m_dbFileName);

        const std::string tmpFileName = "tmpFile";
        std::ofstream tmpFile(tmpFileName);

        while (!in.eof())
        {
            in.read((char*)&tmp, sizeof(T));

            ++i;

            if (i == index)
            {
                tmpFile.write((char*)&f, sizeof(f));
            }

            tmpFile.write((char*)&tmp, sizeof(tmp));       
        }

        in.close();
        tmpFile.close();

        std::remove(m_dbFileName.c_str());
        std::rename(tmpFileName.c_str(), m_dbFileName.c_str());
    }

    void eraseByIndex(const int& index)
    {
        if (index >= m_size || index < 0)
        {
            throw std::exception("out of range!");
        }

        int i = -1;

        T tmp;

        std::fstream in(m_dbFileName);

        const std::string tmpFileName = "tmpFile";
        std::ofstream tmpFile(tmpFileName);

        while (!in.eof())
        {
            in.read((char*)&tmp, sizeof(T));

            ++i;

            if (i == index)
            {
                continue;
            }

            tmpFile.write((char*)&tmp, sizeof(tmp));
        }

        in.close();
        tmpFile.close();

        std::remove(m_dbFileName.c_str());
        std::rename(tmpFileName.c_str(), m_dbFileName.c_str());
    }

    void erase(const T& f)
    {
        T tmp;
        bool E = false;

        std::fstream in(m_dbFileName);

        const std::string tmpFileName = "tmpFile";
        std::ofstream tmpFile(tmpFileName);

        while (!in.eof())
        {
            in.read((char*)&tmp, sizeof(T));

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

        std::remove(m_dbFileName.c_str());
        std::rename(tmpFileName.c_str(), m_dbFileName.c_str());
    }

    // обновление строки
    void replace(const T& f, const int& index)
    {
        if (index >= m_size || index < 0)
        {
            throw std::exception("out of range!");
        }

        std::fstream in(m_dbFileName);

        in.seekg(sizeof(T) * index, std::ios::beg);
 

        in.write((char*)&f, sizeof(T));
    }

    int size()
    {
        return m_size;
    }

    // извлечение строки
    T operator[](const int& index)
    {
        if (index >= m_size || index < 0)
        {
            throw std::exception("out of range!");
        }

        std::fstream in(m_dbFileName);
        T tmp;
        in.seekg(sizeof(tmp) * static_cast<unsigned int>(index), std::ios::beg);
        
        in.read((char*)&tmp, sizeof(T));

        return tmp;
    }
private:
    std::string m_dbFileName;
    int m_size;
};