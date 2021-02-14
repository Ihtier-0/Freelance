#include <string>
#include <fstream>
#include <exception>
#include <cstdio>
#include <functional>

using namespace std;

// шаблонная функция внешней сортировки слиянием
template<class T>
// входные параметры: имя файла, количество записей в файле
void sort(const string& fileName, const int& size)
{
    // размер серии, количество данных в 1м и 2м временных файлах
    int k, i, j;
    // временные переменные нужного типа для 1го и 2го файла
    T t1, t2;

    // потоки ввода из файлов
    std::ifstream fi, fi1, fi2;
    // потоки вывода из файлов
    std::ofstream fo, fo1, fo2;

    // начальный размер серии равен 1
    k = 1;

    // пока размер серии меньше данных в файле
    while (k < size)
    {
        // открываем основной файл на ввод
        fi.open(fileName);
        // открываем временные файлы на вывод
        fo1.open("smsort_tmp_1");
        fo2.open("smsort_tmp_2");

        // если файл не пустой, считываем первый элемент
        if (!fi.eof())
        {
            fi >> t1;
        }

        // если файлл не пустой
        while (!fi.eof())
        {
            // берём к файлов из основного и записываем в 1й временный файл
            for (i = 0; i < k && !fi.eof(); i++)
            {
                fo1 << t1;
                fi >> t1;
            }
            // берём к файлов из основного и записываем в 2й временный файл
            for (j = 0; j < k && !fi.eof(); j++)
            {
                fo2 << t1;
                fi >> t1;
            }
        }
        // закрываем открытые файлы
        fi.close();
        fo1.close();
        fo2.close();

        // открываем основной файл на запись
        fo.open(fileName);
        // открываем временные файлы на чтение
        fi1.open("smsort_tmp_1");
        fi2.open("smsort_tmp_2");

        // считываем по 1й записи из каждого файла
        if (!fi1.eof())
        {
            fi1 >> t1;
        }
        if (!fi2.eof())
        {
            fi2 >> t2;
        }

        // пока оба файла не пусты
        while (!fi1.eof() && !fi2.eof())
        {
            i = 0;
            j = 0;

            // пока серия не закончилась и пока файлы не пусты
            while (i < k && j < k && !fi1.eof() && !fi2.eof())
            {
                // если данные из первого файла меньше
                // записываем данные из первого файла в основной файл и считываем из первого ещё раз
                if (t1 < t2)
                {
                    fo << t1;
                    fi1 >> t1;
                    i++;
                }
                // если данные из первого файла не меньше
                // записываем данные из второго файла в основной файл и считываем из второго ещё раз
                else
                {
                    fo << t2;
                    fi2 >> t2;
                    j++;
                }
            }

            // дозапись оставшихся элементов текущей серии из первого файла
            while (i < k && !fi1.eof())
            {
                fo << t1;
                fi1 >> t1;
                i++;
            }

            // дозапись оставшихся элементов текущей серии из второго файла
            while (j < k && !fi2.eof())
            {
                fo << t2;
                fi2 >> t2;
                j++;
            }
        }

        // дозапись оставшихся элементов из первого файла
        while (!fi1.eof())
        {
            fo << t1;
            fi1 >> t1;
        }
        // дозапись оставшихся элементов из второго файла
        while (!fi2.eof())
        {
            fo << t2;
            fi2 >> t2;
        }

        // закрытие файла
        fi1.close();
        fi2.close();
        fo.close();
        // увеличение серии в 2 раза
        k *= 2;
    }
    // закрытие всех файлов
    fi1.close();
    fi2.close();
    fo.close();

    // удаление временных файлов
    remove("smsort_tmp_1");
    remove("smsort_tmp_2");
}

// класс человек
class Person
{
public:
    // конструктор по умолчанию
    Person() : m_fullName(), m_address(), m_phoneNumber(0) {}
    // конструктор принимающий все данные о человеке
    Person(const string& a_fullName,
        const string& a_address,
        const unsigned long long& a_phoneNumber)
        : m_fullName(a_fullName), m_address(a_address), m_phoneNumber(a_phoneNumber) {}
    // перегрузка операторов сравнения, сравнение производится по номеру телефону
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

    // перегрузка оператора вывода
    friend ostream& operator<<(ostream& out, const Person& p)
    {
        out << p.m_phoneNumber << '\n'
            << p.m_fullName << '\n'
            << p.m_address << '\n';

        return out;
    }

    // перегрузка оператора ввода
    friend istream& operator>>(istream& is, Person& p)
    {
        is >> p.m_phoneNumber >> p.m_fullName >> p.m_address;

        return is;
    }

private:
    // ФИО
    string m_fullName;
    // адрес
    string m_address;
    // номер телефона
    unsigned long long m_phoneNumber;
};

int main()
{
    // данные записываются в файл в указанном порядке
    ofstream out("db.txt");
    out << Person("Ivan", "Russia", 2);
    out << Person("Ivan", "Russia", 4);
    out << Person("Ivan", "Russia", 3);
    out << Person("Ivan", "Russia", 5);
    out << Person("Ivan", "Russia", 6);
    out << Person("Ivan", "Russia", 1);
    out.close();

    // сортировка данных из файла
    sort<Person>("db.txt", 6);
}