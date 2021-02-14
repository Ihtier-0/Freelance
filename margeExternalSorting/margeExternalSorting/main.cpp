#include <string>
#include <fstream>
#include <exception>
#include <cstdio>
#include <functional>

using namespace std;

// ��������� ������� ������� ���������� ��������
template<class T>
// ������� ���������: ��� �����, ���������� ������� � �����
void sort(const string& fileName, const int& size)
{
    // ������ �����, ���������� ������ � 1� � 2� ��������� ������
    int k, i, j;
    // ��������� ���������� ������� ���� ��� 1�� � 2�� �����
    T t1, t2;

    // ������ ����� �� ������
    std::ifstream fi, fi1, fi2;
    // ������ ������ �� ������
    std::ofstream fo, fo1, fo2;

    // ��������� ������ ����� ����� 1
    k = 1;

    // ���� ������ ����� ������ ������ � �����
    while (k < size)
    {
        // ��������� �������� ���� �� ����
        fi.open(fileName);
        // ��������� ��������� ����� �� �����
        fo1.open("smsort_tmp_1");
        fo2.open("smsort_tmp_2");

        // ���� ���� �� ������, ��������� ������ �������
        if (!fi.eof())
        {
            fi >> t1;
        }

        // ���� ����� �� ������
        while (!fi.eof())
        {
            // ���� � ������ �� ��������� � ���������� � 1� ��������� ����
            for (i = 0; i < k && !fi.eof(); i++)
            {
                fo1 << t1;
                fi >> t1;
            }
            // ���� � ������ �� ��������� � ���������� � 2� ��������� ����
            for (j = 0; j < k && !fi.eof(); j++)
            {
                fo2 << t1;
                fi >> t1;
            }
        }
        // ��������� �������� �����
        fi.close();
        fo1.close();
        fo2.close();

        // ��������� �������� ���� �� ������
        fo.open(fileName);
        // ��������� ��������� ����� �� ������
        fi1.open("smsort_tmp_1");
        fi2.open("smsort_tmp_2");

        // ��������� �� 1� ������ �� ������� �����
        if (!fi1.eof())
        {
            fi1 >> t1;
        }
        if (!fi2.eof())
        {
            fi2 >> t2;
        }

        // ���� ��� ����� �� �����
        while (!fi1.eof() && !fi2.eof())
        {
            i = 0;
            j = 0;

            // ���� ����� �� ����������� � ���� ����� �� �����
            while (i < k && j < k && !fi1.eof() && !fi2.eof())
            {
                // ���� ������ �� ������� ����� ������
                // ���������� ������ �� ������� ����� � �������� ���� � ��������� �� ������� ��� ���
                if (t1 < t2)
                {
                    fo << t1;
                    fi1 >> t1;
                    i++;
                }
                // ���� ������ �� ������� ����� �� ������
                // ���������� ������ �� ������� ����� � �������� ���� � ��������� �� ������� ��� ���
                else
                {
                    fo << t2;
                    fi2 >> t2;
                    j++;
                }
            }

            // �������� ���������� ��������� ������� ����� �� ������� �����
            while (i < k && !fi1.eof())
            {
                fo << t1;
                fi1 >> t1;
                i++;
            }

            // �������� ���������� ��������� ������� ����� �� ������� �����
            while (j < k && !fi2.eof())
            {
                fo << t2;
                fi2 >> t2;
                j++;
            }
        }

        // �������� ���������� ��������� �� ������� �����
        while (!fi1.eof())
        {
            fo << t1;
            fi1 >> t1;
        }
        // �������� ���������� ��������� �� ������� �����
        while (!fi2.eof())
        {
            fo << t2;
            fi2 >> t2;
        }

        // �������� �����
        fi1.close();
        fi2.close();
        fo.close();
        // ���������� ����� � 2 ����
        k *= 2;
    }
    // �������� ���� ������
    fi1.close();
    fi2.close();
    fo.close();

    // �������� ��������� ������
    remove("smsort_tmp_1");
    remove("smsort_tmp_2");
}

// ����� �������
class Person
{
public:
    // ����������� �� ���������
    Person() : m_fullName(), m_address(), m_phoneNumber(0) {}
    // ����������� ����������� ��� ������ � ��������
    Person(const string& a_fullName,
        const string& a_address,
        const unsigned long long& a_phoneNumber)
        : m_fullName(a_fullName), m_address(a_address), m_phoneNumber(a_phoneNumber) {}
    // ���������� ���������� ���������, ��������� ������������ �� ������ ��������
    friend bool operator<(const Person& left, const Person& right)
    {
        return left.m_phoneNumber < right.m_phoneNumber;
    }
    friend bool operator>(const Person& left, const Person& right)
    {
        return left.m_phoneNumber > right.m_phoneNumber;
    }
    friend bool operator==(const Person& left, const Person& right)
    {
        return left.m_phoneNumber == right.m_phoneNumber;
    }
    friend bool operator!=(const Person& left, const Person& right)
    {
        return left.m_phoneNumber != right.m_phoneNumber;
    }
    friend bool operator>=(const Person& left, const Person& right)
    {
        return left.m_phoneNumber >= right.m_phoneNumber;
    }
    friend bool operator<=(const Person& left, const Person& right)
    {
        return left.m_phoneNumber <= right.m_phoneNumber;
    }

    // ���������� ��������� ������
    friend ostream& operator<<(ostream& out, const Person& p)
    {
        out << p.m_phoneNumber << '\n'
            << p.m_fullName << '\n'
            << p.m_address << '\n';

        return out;
    }

    // ���������� ��������� �����
    friend istream& operator>>(istream& is, Person& p)
    {
        is >> p.m_phoneNumber >> p.m_fullName >> p.m_address;

        return is;
    }

private:
    // ���
    string m_fullName;
    // �����
    string m_address;
    // ����� ��������
    unsigned long long m_phoneNumber;
};

int main()
{
    // ������ ������������ � ���� � ��������� �������
    ofstream out("db.txt");
    out << Person("Ivan", "Russia", 2);
    out << Person("Ivan", "Russia", 4);
    out << Person("Ivan", "Russia", 3);
    out << Person("Ivan", "Russia", 5);
    out << Person("Ivan", "Russia", 6);
    out << Person("Ivan", "Russia", 1);
    out.close();

    // ���������� ������ �� �����
    sort<Person>("db.txt", 6);
}