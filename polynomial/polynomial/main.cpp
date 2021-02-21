#include <iostream>
#include <vector>

using namespace std;

class polynomial
{
public:
	polynomial() : m_polynomialCoefficient(nullptr), m_degree(0) {}

	polynomial(const double const* const &a_polynomialCoefficient, const int& a_degree) : m_degree(a_degree + 1)
	{
		m_polynomialCoefficient = new double[m_degree];

		for (int i = 0; i < m_degree; ++i)
		{
			m_polynomialCoefficient[i] = a_polynomialCoefficient[i];
		}
	}

	polynomial(const int& a_degree) : m_degree(a_degree + 1)
	{
		m_polynomialCoefficient = new double[m_degree];

		for (int i = 0; i < m_degree; ++i)
		{
			m_polynomialCoefficient[i] = 0;
		}
	}

	polynomial(const polynomial& p) : m_degree(p.m_degree)
	{
		m_polynomialCoefficient = new double[m_degree];

		for (int i = 0; i < m_degree; ++i)
		{
			m_polynomialCoefficient[i] = p.m_polynomialCoefficient[i];
		}
	}

	int degree()
	{
		return m_degree - 1;
	}

	~polynomial()
	{
		if (m_polynomialCoefficient)
		{
			delete[] m_polynomialCoefficient;
		}
		m_degree = 0;
	}

	double calculate(const double& x)
	{
		double result = 0, pow = 1;

		for (int i = 0; i < m_degree; i++)
		{
			result += pow * m_polynomialCoefficient[i];
			pow *= x;
		}

		return result;
	}
private:
	double *m_polynomialCoefficient;
	int m_degree = 0;

	friend polynomial operator+(const polynomial& p1, const polynomial& p2)
	{
		if (p1.m_degree != p2.m_degree)
		{
			return polynomial();
		}

		polynomial result(p1);

		for (int i = 0; i < p1.m_degree; i++)
		{
			result.m_polynomialCoefficient[i] += p2.m_polynomialCoefficient[i];
		}

		return result;
	}
	friend polynomial operator-(const polynomial& p1, const polynomial& p2)
	{
		if (p1.m_degree != p2.m_degree)
		{
			return polynomial();
		}

		polynomial result(p1);

		for (int i = 0; i < p1.m_degree; i++)
		{
			result.m_polynomialCoefficient[i] -= p2.m_polynomialCoefficient[i];
		}

		return result;
	}
	friend polynomial operator*(const polynomial& left, const polynomial& right)
	{
		int leftDegree = left.m_degree;
		int rightDegree = right.m_degree;

		polynomial result(leftDegree + rightDegree - 2);

		for (int i = 0; i < leftDegree; ++i)
		{
			for (int j = 0; j < rightDegree; ++j)
			{
				result.m_polynomialCoefficient[i + j] += left.m_polynomialCoefficient[i] * right.m_polynomialCoefficient[j];
			}
		}

		return result;
	}
	friend ostream& operator<<(ostream &out, const polynomial& p2)
	{
		for (int i = 0; i < p2.m_degree; i++)
		{
			cout << p2.m_polynomialCoefficient[i] << " * x^" << i;

			if (i != p2.m_degree - 1)
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
	polynomial p1(p11, 2), p2(p22, 2);
	cout << "p1(x) = " << p1 << '\n';
	cout << "p2(x) = " << p2 << "\n\n";

	cout << "p1(2) = " << p1.calculate(2) << '\n';
	cout << "p2(2) = " << p2.calculate(2) << "\n\n";

	cout << "p1 degree = " << p1.degree() << '\n';
	cout << "p2 degree = " << p2.degree() << "\n\n";

	cout << "(p1 + p2)(x) = " << p1 + p2 << '\n';
	cout << "(p1 - p2)(x) = " << p1 - p2 << "\n\n";

	cout << "(p1 + p2)(2) = " << (p1 + p2).calculate(2) << '\n';
	cout << "(p1 - p2)(2) = " << (p1 - p2).calculate(2) << "\n\n";

	cout << "(p1 * p2)(x) = " << p1 * p2 << '\n';
	cout << "(p2 * p1)(x) = " << p2 * p1 << "\n\n";

	cout << "(p1 * p2)(1) = " << (p1 * p2).calculate(1) << '\n';
	cout << "p1(1) * p2(1) = " << p1.calculate(1) * p2.calculate(1) << "\n\n";

	cout << "(p2 * p1)(1) = " << (p2 * p1).calculate(1) << '\n';
	cout << "p2(1) * p1(1) = " << p2.calculate(1) * p1.calculate(1) << "\n\n";
}