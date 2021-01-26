#include <string>
#include <iostream>

using namespace std;

class fruit
{
public:
	fruit() : m_color(), m_weight(0) {}
	fruit(const string& a_color, const double& a_weight) : m_color(a_color), m_weight(a_weight) {};
	fruit(const fruit& f) : m_color(f.m_color), m_weight(f.m_weight) {};
	~fruit() {}

	virtual void print()
	{
		cout << m_color << ' ' << m_weight;
	}

protected:
	string m_color;
	double m_weight;
};

class grapes : public fruit
{
public:
	grapes() : fruit(), m_numberOfBerries(0) {}
	grapes(const string& a_color, const double& a_weight, const int& a_numberOfBerries)
		: fruit(a_color, a_weight), m_numberOfBerries(a_numberOfBerries) {};
	grapes(const grapes& f) : fruit(f), m_numberOfBerries(f.m_numberOfBerries) {};
	void print() override
	{
		cout << "grapes " << m_numberOfBerries << ' ';
		fruit::print();
	}

	~grapes() {}
private:
	int m_numberOfBerries;
};

class apple : public fruit
{
public:
	apple() : fruit(), m_variety() {}
	apple(const string& a_color, const double& a_weight, const string& a_variety)
		: fruit(a_color, a_weight), m_variety(a_variety) {};
	apple(const apple& f) : fruit(f), m_variety(f.m_variety) {};
	void print() override
	{
		cout << "apple " << m_variety << ' ';
		fruit::print();
	}

	~apple() {}
private:
	string m_variety;
};

int main()
{
	int size = 4;

	fruit** a = new fruit * [size];

	a[0] = new apple("red", 12, "cool");
	a[1] = new apple("green", 150, "cool");
	a[2] = new grapes("red", 3, 10);
	a[3] = new grapes("green", 2, 100);

	for (int i = 0; i < size; ++i)
	{
		a[i]->print();
		cout << '\n';
	}

	for (int i = 0; i < size; ++i)
	{
		delete a[i];
	}

	delete[] a;
}