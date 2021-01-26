#include <iostream>

using namespace std;

class list
{
public:
	list() : m_size(0), m_list(nullptr) {}

	list(const double const* const& a_list, const int& a_size) : m_size(a_size)
	{
		m_list = new double[m_size];

		for (int i = 0; i < m_size; ++i)
		{
			m_list[i] = a_list[i];
		}
	}

	list(const list& l) : m_size(l.m_size)
	{
		m_list = new double[m_size];

		for (int i = 0; i < m_size; ++i)
		{
			m_list[i] = l.m_list[i];
		}
	}

	void push_back(const double& x)
	{
		double* new_list = new double[m_size + 1];

		for (int i = 0; i < m_size; ++i)
		{
			new_list[i] = m_list[i];
		}

		new_list[m_size] = x;

		if (m_list)
		{
			delete[] m_list;
		}

		++m_size;
		m_list = new_list;
	}

	void erase(const double& x)
	{
		int index = -1;

		for (int i = 0; i < m_size; ++i)
		{
			if (m_list[i] == x)
			{
				index = i;
				break;
			}
		}

		if (index == -1)
		{
			return;
		}
		// 
		double* new_list = new double[m_size - 1];

		for (int i = 0; i < index; ++i)
		{
			new_list[i] = m_list[i];
		}
		for (int i = index; i < m_size - 1; ++i)
		{
			new_list[i] = m_list[i + 1];
		}

		if (m_list)
		{
			delete[] m_list;
		}

		--m_size;
		m_list = new_list;
	}

	~list()
	{
		if (m_list)
		{
			delete[] m_list;
		}
		m_size = 0;
	}

private:
	double* m_list;
	int m_size;

	friend ostream& operator<<(ostream& out, const list& l)
	{
		for (int i = 0; i < l.m_size; ++i)
		{
			out << l.m_list[i] << ' ';
		}
		return out;
	}
};

int main()
{
	list l;

	l.push_back(0);
	l.push_back(2);
	l.push_back(-1);
	l.push_back(7);
	l.push_back(-5);
	l.push_back(100);
	l.push_back(-10);

	cout << l << '\n';

	l.erase(0);
	l.erase(100);
	l.erase(7);
	l.erase(-5);
	l.erase(10000);

	cout << l << '\n';
}