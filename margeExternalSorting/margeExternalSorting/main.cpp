#include <string>
#include <fstream>
#include <exception>
#include <cstdio>
#include <functional>

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

int main()
{

}