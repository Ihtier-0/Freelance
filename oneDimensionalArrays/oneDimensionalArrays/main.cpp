#include <iostream>

using namespace std;

// класс одномерного массива
class oneDimentionArray
{
public:
	// конструктор по умолчанию
	oneDimentionArray() : m_size(0), m_array(nullptr){}
	// конструктор который принимает только размер и заполняет массив 0-ми
	oneDimentionArray(const int& a_size) : m_size(a_size), m_array(new int[a_size])
	{
		for (int i = 0; i < m_size; ++i)
		{
			m_array[i] = 0;
		}
	}
	// конструктор который принимает размер и массив который надо сохранить
	oneDimentionArray(const int& a_size, const int const * const &a_array) : m_size(a_size), m_array(new int[a_size])
	{
		for (int i = 0; i < m_size; ++i)
		{
			m_array[i] = a_array[i];
		}
	}
	// конструктор копирования, очень похож на конструктор выше
	oneDimentionArray(const oneDimentionArray& o) : m_size(o.m_size)
	{
		m_array = new int[m_size];

		for (int i = 0; i < m_size; ++i)
		{
			m_array[i] = o.m_array[i];
		}
	}
	// деструктор
	~oneDimentionArray()
	{
		// если массив не пустой удаляем его, размер = 0
		if (m_array)
		{
			delete[] m_array;
			m_size = 0;
		}
	}
	// оператор доступа по индексу
	int& operator[] (const int& index)
	{
		// если индекс меньше 0 или больше чем размер бросаем исключение
		if (index < 0 || index >= m_size)
		{
			throw exception();
		}

		// если нет возвращаем нужный элемент, по ссылке чтобы было возможно делать так oneDimentionArray[i] = 5
		return m_array[index];
	}
private:
	// размер
	int m_size;
	// сам массив
	int* m_array;

	// друженственная функция сложения
	friend oneDimentionArray operator+(const oneDimentionArray& o1, const oneDimentionArray& o2)
	{
		// если размеры разные сложить невозможно, возвращем пустой массив
		if (o1.m_size != o2.m_size)
		{
			return oneDimentionArray();
		}

		// если одинаковый размер, то поэлементно складываем
		oneDimentionArray result(o1);

		for (int i = 0; i < o1.m_size; ++i)
		{
			result.m_array[i] += o2.m_array[i];
		}

		return result;
	}

	// друженственный оператор вычитания
	friend oneDimentionArray operator-(const oneDimentionArray& o1, const oneDimentionArray& o2)
	{
		// если размеры разные вычесть невозможно, возвращем пустой массив
		if (o1.m_size != o2.m_size)
		{
			return oneDimentionArray();
		}
		// если одинаковый размер, то поэлементно вычитаем
		oneDimentionArray result(o1);

		for (int i = 0; i < o1.m_size; ++i)
		{
			result.m_array[i] -= o2.m_array[i];
		}

		return result;
	}

	// дружественны оператор умножения на число
	friend oneDimentionArray operator*(const oneDimentionArray& o1, const int& k)
	{
		// умножаем каждый элемент на число
		oneDimentionArray result(o1);

		for (int i = 0; i < o1.m_size; ++i)
		{
			result.m_array[i] *= k;
		}

		return result;
	}

	// перегрузка оператора деления
	friend oneDimentionArray operator/(const oneDimentionArray& o1, const int& k)
	{
		// делить на 0 запрещено, возвращаем пустой массив
		if (k == 0)
		{
			return oneDimentionArray();
		}

		// если не 0, то можем делать 
		oneDimentionArray result(o1);

		for (int i = 0; i < o1.m_size; ++i)
		{
			result.m_array[i] /= k;
		}

		return result;
	}

	// не важно как умножать на число слева или справа, поэтому так
	friend oneDimentionArray operator*(const int& k, const oneDimentionArray& o1)
	{
		return o1 * k;
	}

	// перегрузка оператора вывода
	friend ostream& operator<< (ostream& out, const  oneDimentionArray& o1)
	{
		for (int i = 0; i < o1.m_size; ++i)
		{
			out << o1.m_array[i] << ' ';
		}

		return out;
	}
};

template<class T>
class templateOneDimentionArray
{
public:
	templateOneDimentionArray() : m_size(0), m_array(nullptr) {}
	templateOneDimentionArray(const int& a_size) : m_size(a_size), m_array(new int[a_size]) {}
	templateOneDimentionArray(const int& a_size, const T const* const& a_array) : m_size(a_size), m_array(new T[a_size])
	{
		for (int i = 0; i < m_size; ++i)
		{
			m_array[i] = a_array[i];
		}
	}
	templateOneDimentionArray(const templateOneDimentionArray& o) : m_size(o.m_size)
	{
		m_array = new T[m_size];

		for (int i = 0; i < m_size; ++i)
		{
			m_array[i] = o.m_array[i];
		}
	}
	~templateOneDimentionArray()
	{
		if (m_array)
		{
			delete[] m_array;
			m_size = 0;
		}
	}
	T& operator[] (const int& index)
	{
		if (index < 0 || index >= m_size)
		{
			throw exception();
		}

		return m_array[index];
	}
private:
	int m_size;
	T* m_array;

	friend templateOneDimentionArray operator+(const templateOneDimentionArray& o1, const templateOneDimentionArray& o2)
	{
		if (o1.m_size != o2.m_size)
		{
			return templateOneDimentionArray();
		}

		templateOneDimentionArray result(o1);

		for (int i = 0; i < o1.m_size; ++i)
		{
			result.m_array[i] += o2.m_array[i];
		}

		return result;
	}

	friend templateOneDimentionArray operator-(const templateOneDimentionArray& o1, const templateOneDimentionArray& o2)
	{
		if (o1.m_size != o2.m_size)
		{
			return templateOneDimentionArray();
		}

		templateOneDimentionArray result(o1);

		for (int i = 0; i < o1.m_size; ++i)
		{
			result.m_array[i] -= o2.m_array[i];
		}

		return result;
	}

	friend templateOneDimentionArray operator*(const templateOneDimentionArray& o1, const int& k)
	{
		templateOneDimentionArray result(o1);

		for (int i = 0; i < o1.m_size; ++i)
		{
			result.m_array[i] *= k;
		}

		return result;
	}

	friend templateOneDimentionArray operator/(const templateOneDimentionArray& o1, const int& k)
	{
		if (k == 0)
		{
			return templateOneDimentionArray();
		}

		templateOneDimentionArray result(o1);

		for (int i = 0; i < o1.m_size; ++i)
		{
			result.m_array[i] /= k;
		}

		return result;
	}

	friend templateOneDimentionArray operator*(const int& k, const templateOneDimentionArray& o1)
	{
		return o1 * k;
	}

	friend ostream& operator<< (ostream& out, const  templateOneDimentionArray& o1)
	{
		for (int i = 0; i < o1.m_size; ++i)
		{
			out << o1.m_array[i] << ' ';
		}

		return out;
	}
};

int main()
{
	int p1[] = { 3,2,1 };
	oneDimentionArray o1(3, p1);
	int p2[] = { -3,2,-1 };
	oneDimentionArray o2(3, p2);
	
	cout << "o1\n" << o1 << "\no2\n" << o2 << "\no1 + o2\n" << o1 + o2
		<< "\no1 - o2\n" << o1 - o2 << "\n2 * o1\n" << 2 * o1 << "\no1 / 2\n" << o1 / 2 << '\n';
	cout << "o2[1] = " << o2[1] << '\n';
	o2[1] = 3;
	cout << "o2[1] = " << o2[1] << '\n';

	cout << "\n\n";

	double T1[] = { 3.1,2.5,1.1 };
	templateOneDimentionArray<double> t1(3, T1);
	double T2[] = { -3.3,2.8,-1.9 };
	templateOneDimentionArray<double> t2(3, T2);

	cout << "t1\n" << t1 << "\nt2\n" << t2 << "\nt1 + t2\n" << t1 + t2
		<< "\nt1 - t2\n" << t1 - t2 << "\n2 * t1\n" << 2 * t1 << "\nt1 / 2\n" << t1 / 2. << '\n';
}