#include <iostream>

using namespace std;

class money
{
public:
	money() : m_rubles(0), m_penny(0) {}
	money(const long& a_rubles, const unsigned char a_penny) : m_rubles(a_rubles), m_penny(a_penny)
	{
		if (m_penny >= 100)
		{
			m_rubles += m_penny / 100;
			m_penny %= 100;
		}
	}
private:
	long m_rubles;
	unsigned char m_penny;

	friend money operator+(const money& m1, const money& m2)
	{
		long rubles = m1.m_rubles + m2.m_rubles;
		long penny = static_cast<long>(m1.m_penny) + static_cast<long>(m2.m_penny);

		rubles += penny / 100;
		penny %= 100;

		return money(rubles, penny);
	}
	friend money operator-(const money& m1, const money& m2)
	{
		long rubles = m1.m_rubles - m2.m_rubles;
		long penny = static_cast<long>(m1.m_penny) - static_cast<long>(m2.m_penny);

		rubles += penny / 100;
		penny %= 100;

		if (penny < 0)
		{
			rubles -= 1;
			penny += 100;
		}

		return money(rubles, penny);
	}

	friend money operator*(const money& m1, const double& k)
	{
		long rubles = static_cast<double>(m1.m_rubles) * k;
		long penny = static_cast<double>(m1.m_penny) * k;

		rubles += penny / 100;
		penny %= 100;

		return money(rubles, penny);
	}

	friend money operator*(const double& k, const money& m1)
	{
		return m1 * k;
	}

	friend money operator/(const money& m1, const double& k)
	{
		long rubles = static_cast<double>(m1.m_rubles) / k;
		long penny = static_cast<double>(m1.m_penny) / k;

		rubles += penny / 100;
		penny %= 100;

		return money(rubles, penny);
	}

	friend bool operator<(const money& m1, const money& m2)
	{
		return (m1.m_rubles < m2.m_rubles) ||
			(m1.m_rubles == m2.m_rubles && m1.m_rubles < m2.m_rubles);
	}

	friend bool operator>(const money& m1, const money& m2)
	{
		return (m1.m_rubles > m2.m_rubles) ||
			(m1.m_rubles == m2.m_rubles && m1.m_rubles > m2.m_rubles);
	}

	friend bool operator==(const money& m1, const money& m2)
	{
		return m1.m_penny == m2.m_penny && m1.m_rubles == m2.m_rubles;
	}

	friend bool operator<=(const money& m1, const money& m2)
	{
		return m1 < m2 || m1 == m2;
	}

	friend bool operator>=(const money& m1, const money& m2)
	{
		return m1 > m2 || m1 == m2;
	}

	friend bool operator!=(const money& m1, const money& m2)
	{
		return !(m1 == m2);
	}

	friend ostream& operator<< (ostream& out, const money& m)
	{
		cout << m.m_rubles << ',' << static_cast<int>(m.m_penny);

		return out;
	}
};

int main()
{
	money m1(100, 50), m2(10, 70);

	cout << "m1 " << m1 << " rub\nm2 " << m2 << " rub\n";
	cout << "m1 + m2 " << m1 + m2 << " rub\n";
	cout << "m1 - m2 " << m1 - m2 << " rub\n";
	cout << "m1 * 2 " << m1 * 2 << " rub\n";
	cout << "m1 / 2 " << m1 / 2 << " rub\n";

	if (m1 < m2)
	{
		cout << "m1 < m2\n";
	}
	else
	{
		cout << "!(m1 < m2)\n";
	}

	if (m1 == m2)
	{
		cout << "m1 == m2\n";
	}
	else
	{
		cout << "!(m1 == m2)\n";
	}

	if (m1 > m2)
	{
		cout << "m1 > m2\n";
	}
	else
	{
		cout << "!(m1 > m2)\n";
	}
}