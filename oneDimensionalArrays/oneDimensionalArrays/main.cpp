#include <iostream>

using namespace std;

// ����� ����������� �������
class oneDimentionArray
{
public:
	// ����������� �� ���������
	oneDimentionArray() : m_size(0), m_array(nullptr){}
	// ����������� ������� ��������� ������ ������ � ��������� ������ 0-��
	oneDimentionArray(const int& a_size) : m_size(a_size), m_array(new int[a_size])
	{
		for (int i = 0; i < m_size; ++i)
		{
			m_array[i] = 0;
		}
	}
	// ����������� ������� ��������� ������ � ������ ������� ���� ���������
	oneDimentionArray(const int& a_size, const int const * const &a_array) : m_size(a_size), m_array(new int[a_size])
	{
		for (int i = 0; i < m_size; ++i)
		{
			m_array[i] = a_array[i];
		}
	}
	// ����������� �����������, ����� ����� �� ����������� ����
	oneDimentionArray(const oneDimentionArray& o) : m_size(o.m_size)
	{
		m_array = new int[m_size];

		for (int i = 0; i < m_size; ++i)
		{
			m_array[i] = o.m_array[i];
		}
	}
	// ����������
	~oneDimentionArray()
	{
		// ���� ������ �� ������ ������� ���, ������ = 0
		if (m_array)
		{
			delete[] m_array;
			m_size = 0;
		}
	}
	// �������� ������� �� �������
	int& operator[] (const int& index)
	{
		// ���� ������ ������ 0 ��� ������ ��� ������ ������� ����������
		if (index < 0 || index >= m_size)
		{
			throw exception();
		}

		// ���� ��� ���������� ������ �������, �� ������ ����� ���� �������� ������ ��� oneDimentionArray[i] = 5
		return m_array[index];
	}
private:
	// ������
	int m_size;
	// ��� ������
	int* m_array;

	// �������������� ������� ��������
	friend oneDimentionArray operator+(const oneDimentionArray& o1, const oneDimentionArray& o2)
	{
		// ���� ������� ������ ������� ����������, ��������� ������ ������
		if (o1.m_size != o2.m_size)
		{
			return oneDimentionArray();
		}

		// ���� ���������� ������, �� ����������� ����������
		oneDimentionArray result(o1);

		for (int i = 0; i < o1.m_size; ++i)
		{
			result.m_array[i] += o2.m_array[i];
		}

		return result;
	}

	// �������������� �������� ���������
	friend oneDimentionArray operator-(const oneDimentionArray& o1, const oneDimentionArray& o2)
	{
		// ���� ������� ������ ������� ����������, ��������� ������ ������
		if (o1.m_size != o2.m_size)
		{
			return oneDimentionArray();
		}
		// ���� ���������� ������, �� ����������� ��������
		oneDimentionArray result(o1);

		for (int i = 0; i < o1.m_size; ++i)
		{
			result.m_array[i] -= o2.m_array[i];
		}

		return result;
	}

	// ������������ �������� ��������� �� �����
	friend oneDimentionArray operator*(const oneDimentionArray& o1, const int& k)
	{
		// �������� ������ ������� �� �����
		oneDimentionArray result(o1);

		for (int i = 0; i < o1.m_size; ++i)
		{
			result.m_array[i] *= k;
		}

		return result;
	}

	// ���������� ��������� �������
	friend oneDimentionArray operator/(const oneDimentionArray& o1, const int& k)
	{
		// ������ �� 0 ���������, ���������� ������ ������
		if (k == 0)
		{
			return oneDimentionArray();
		}

		// ���� �� 0, �� ����� ������ 
		oneDimentionArray result(o1);

		for (int i = 0; i < o1.m_size; ++i)
		{
			result.m_array[i] /= k;
		}

		return result;
	}

	// �� ����� ��� �������� �� ����� ����� ��� ������, ������� ���
	friend oneDimentionArray operator*(const int& k, const oneDimentionArray& o1)
	{
		return o1 * k;
	}

	// ���������� ��������� ������
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