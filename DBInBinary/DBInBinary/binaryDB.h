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
        std::ifstream in(m_dbFileName, std::ifstream::ate | std::ifstream::binary);

        if (!in.is_open())
        {
            throw std::exception("File not exist");
        }

        m_size = in.tellg() / sizeof(T);
    }
    
    // добавление строки
    void add(const T& f)
    {
        std::ofstream out(m_dbFileName, std::ios::app);

        out.write((char*)&f, sizeof(T));

        ++m_size;
    }
    
    // вставка по логическому номеру
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

        m_size++;

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

        --m_size;

        std::remove(m_dbFileName.c_str());
        std::rename(tmpFileName.c_str(), m_dbFileName.c_str());
    }
    
    // удаление
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
    
    int size() const
    {
        return m_size;
    }
    
    // сортировка
    void sort()
    {
        int k, i, j, tmp;
        T t1, t2;

        std::ifstream fi, fi1, fi2;
        std::ofstream fo, fo1, fo2;

        k = 1;

        while (k < m_size)
        {
            fi.open(m_dbFileName);
            fo1.open("smsort_tmp_1");
            fo2.open("smsort_tmp_2");

            if (!fi.eof())
            {
                fi.read((char*)&t1, sizeof(T));
            }

            while (!fi.eof())
            {
                for (i = 0; i < k && !fi.eof(); i++)
                {
                    fo1.write((char*)&t1, sizeof(T));
                    fi.read((char*)&t1, sizeof(T));
                }
                for (j = 0; j < k && !fi.eof(); j++)
                {
                    fo2.write((char*)&t1, sizeof(T));
                    fi.read((char*)&t1, sizeof(T));
                }
            }
            fi.close();
            fo1.close();
            fo2.close();

            fo.open(m_dbFileName);
            fi1.open("smsort_tmp_1");
            fi2.open("smsort_tmp_2");

            if (!fi1.eof())
            {
                fi1.read((char*)&t1, sizeof(T));
            }
            if (!fi2.eof())
            {
                fi2.read((char*)&t2, sizeof(T));
            }
                
            while (!fi1.eof() && !fi2.eof())
            {
                i = 0;
                j = 0;

                while (i < k && j < k && !fi1.eof() && !fi2.eof())
                {
                    if (t1 < t2)
                    {
                        fo.write((char*)&t1, sizeof(T));
                        fi1.read((char*)&t1, sizeof(T));
                        i++;
                    }
                    else
                    {
                        fo.write((char*)&t2, sizeof(T));
                        fi2.read((char*)&t2, sizeof(T));
                        j++;
                    }
                }

                while (i < k && !fi1.eof())
                {
                    fo.write((char*)&t1, sizeof(T));
                    fi1.read((char*)&t1, sizeof(T));
                    i++;
                }

                while (j < k && !fi2.eof())
                {
                    fo.write((char*)&t2, sizeof(T));
                    fi2.read((char*)&t2, sizeof(T));
                    j++;
                }
            }

            while (!fi1.eof())
            {
                fo.write((char*)&t1, sizeof(T));
                fi1.read((char*)&t1, sizeof(T));
            }
            while (!fi2.eof())
            {
                fo.write((char*)&t2, sizeof(T));
                fi2.read((char*)&t2, sizeof(T));
            }

            fi1.close();
            fi2.close();
            fo.close();
            k *= 2;
        }
        fi1.close();
        fi2.close();
        fo.close();

        remove("smsort_tmp_1");
        remove("smsort_tmp_2");
    }
    
    // вставка с сохранением порядка
    void addWithKeepingOrder(const T& f)
    {
        std::fstream file(m_dbFileName);

        int i = 0;
        T tmp;
        file.read((char*)&tmp, sizeof(T));

        while (tmp < f && i < m_size)
        {
            file.read((char*)&tmp, sizeof(T));
            ++i;
        }

        file.close();

        this->addByIndex(f, i);
    }

    // извлечение строки
    T operator[](const int& index) const
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

    friend std::ostream& operator<<(std::ostream& out, const binaryDB<T> db)
    {
        for (int i = 0; i < db.size(); ++i)
        {
            out << db[i] << ' ';
        }

        return out;
    }
private:
    std::string m_dbFileName;
    int m_size;
};