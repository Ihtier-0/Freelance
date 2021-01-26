#include <iostream>
#include <cmath>

using namespace std;

class function
{
public:
	function()
	{
		++m_numberOfFunctions;
	}

	~function()
	{
		--m_numberOfFunctions;
	}

	static int numberOfFunctions()
	{
		return m_numberOfFunctions;
	}

	virtual double calculate(const double& x) = 0;

private:
	static int m_numberOfFunctions;
};

int function::m_numberOfFunctions = 0;

class Sin : public function
{
public:
	double calculate(const double& x)
	{
		return sin(x);
	}
private:
	friend ostream& operator<<(ostream& out, const Sin& s)
	{
		out << "sin(x)";

		return out;
	}
};

class Cos : public function
{
public:
	double calculate(const double& x)
	{
		return cos(x);
	}
private:
	friend ostream& operator<<(ostream& out, const Cos& s)
	{
		out << "cos(x)";

		return out;
	}
};

class Abs : public function
{
public:
	double calculate(const double& x)
	{
		return abs(x);
	}
private:
	friend ostream& operator<<(ostream& out, const Abs& s)
	{
		out << "abs(x)";

		return out;
	}
};

class Sgn : public function
{
public:
	double calculate(const double& x)
	{
		return x > 0 ? 1 : 0;
	}
private:
	friend ostream& operator<<(ostream& out, const Sgn& s)
	{
		out << "sgn(x)";

		return out;
	}
};

int main()
{
	Sin s;
	Cos c;
	Abs a;
	Sgn sg;

	double x = -0.5;
	cout << "x = " << x << '\n';
	cout << s << " = " << s.calculate(x) << '\n';
	cout << c << " = " << c.calculate(x) << '\n';
	cout << a << " = " << a.calculate(x) << '\n';
	cout << sg << " = " << sg.calculate(x) << '\n';
	cout << "numberOfFunctions: " << Sin::numberOfFunctions() << '\n';
	
}