#include <iostream>
#include <vector>

using namespace std;

class polynomial
{
public:
	polynomial() : m_polynomialCoefficient(nullptr), m_size(0) {}

	polynomial(const double const* const &a_polynomialCoefficient, const int& a_size) : m_size(a_size)
	{
		m_polynomialCoefficient = new double[m_size];

		for (int i = 0; i < m_size; ++i)
		{
			m_polynomialCoefficient[i] = a_polynomialCoefficient[i];
		}
	}

	polynomial(const polynomial& p) : m_size(p.m_size)
	{
		m_polynomialCoefficient = new double[m_size];

		for (int i = 0; i < m_size; ++i)
		{
			m_polynomialCoefficient[i] = p.m_polynomialCoefficient[i];
		}
	}

	~polynomial()
	{
		if (m_polynomialCoefficient)
		{
			delete[] m_polynomialCoefficient;
		}
		m_size = 0;
	}

	double calculate(const double& x)
	{
		double result = 0, pow = 1;

		for (int i = 0; i < m_size; i++)
		{
			result += pow * m_polynomialCoefficient[i];
			pow *= x;
		}

		return result;
	}
private:
	double *m_polynomialCoefficient;
	int m_size = 0;

	friend polynomial operator+(const polynomial& p1, const polynomial& p2)
	{
		if (p1.m_size != p2.m_size)
		{
			return polynomial();
		}

		polynomial result(p1);

		for (int i = 0; i < p1.m_size; i++)
		{
			result.m_polynomialCoefficient[i] += p2.m_polynomialCoefficient[i];
		}

		return result;
	}
	friend polynomial operator-(const polynomial& p1, const polynomial& p2)
	{
		if (p1.m_size != p2.m_size)
		{
			return polynomial();
		}

		polynomial result(p1);

		for (int i = 0; i < p1.m_size; i++)
		{
			result.m_polynomialCoefficient[i] -= p2.m_polynomialCoefficient[i];
		}

		return result;
	}
	friend ostream& operator<<(ostream &out, const polynomial& p2)
	{
		for (int i = 0; i < p2.m_size; i++)
		{
			cout << p2.m_polynomialCoefficient[i] << " * x^" << i;

			if (i != p2.m_size - 1)
			{
				cout << " + ";
			}
		}

		return out;
	}
};

int main()
{
	double p11[] = { 1,2,3 }, p22[] = { 3,2,1 };
	polynomial p1(p11, 3), p2(p22, 3);
	cout << "p1(x) = " << p1 << '\n';
	cout << "p2(x) = " << p2 << '\n';

	cout << "p1(2) = " << p1.calculate(2) << '\n';
	cout << "p2(2) = " << p2.calculate(2) << '\n';

	cout << "(p1 + p2)(x) = " << p1 + p2 << '\n';
	cout << "(p1 - p2)(x) = " << p1 - p2 << '\n';

	cout << "(p1 + p2)(2) = " << (p1 + p2).calculate(2) << '\n';
	cout << "(p1 - p2)(2) = " << (p1 - p2).calculate(2) << '\n';
}