#include <string>
#include <iostream>

using namespace std;

class animal
{
public:
	animal() : m_name(), m_age(0), m_habitat() {}
	animal(const string& a_name,
		const int& a_age,
		const string& a_habitat) : m_name(a_name), m_age(a_age), m_habitat(a_habitat) {}
	animal(const animal& a) : m_name(a.m_name), m_age(a.m_age), m_habitat(a.m_habitat) {}

	string name() { return m_name; }
	int age() { return m_age; }
	string habitat() { return m_habitat; }

	void rename(const string& a_name) { m_name = a_name; }
	void setAge(const int& a_age) { m_age = a_age; }
	void setHabitat(const string& a_habitat) { m_habitat = a_habitat; }

	virtual void print(ostream& out) = 0;

protected:
	string m_name;
	int m_age;
	// место обитания
	string m_habitat;
};

class cat : public animal
{
public:
	cat() : animal() {} 
	cat(const string& a_name,
		const int& a_age,
		const string& a_habitat) : animal(a_name, a_age, a_habitat) {}
	cat(const cat& a) : animal(a) {}
	void print(ostream & out)
	{
		out << "cat " << m_name << ' ' << m_age << ' ' << m_habitat;
	}
private:

};

class dog : public animal
{
public:
	dog() : animal() {}
	dog(const string& a_name,
		const int& a_age,
		const string& a_habitat) : animal(a_name, a_age, a_habitat) {}
	dog(const dog& a) : animal(a) {}
	void print(ostream& out)
	{
		out << "dog " << m_name << ' ' << m_age << ' ' << m_habitat;
	}
private:

}; 

class tiger : public animal
{
public:
	tiger() : animal() {}
	tiger(const string& a_name,
		const int& a_age,
		const string& a_habitat) : animal(a_name, a_age, a_habitat) {}
	tiger(const tiger& a) : animal(a) {}
	void print(ostream& out)
	{
		out << "tiger " << m_name << ' ' << m_age << ' ' << m_habitat;
	}
private:

};

class hyena : public animal
{
public:
	hyena() : animal() {}
	hyena(const string& a_name,
		const int& a_age,
		const string& a_habitat) : animal(a_name, a_age, a_habitat) {}
	hyena(const hyena& a) : animal(a) {}
	void print(ostream& out)
	{
		out << "hyena " << m_name << ' ' << m_age << ' ' << m_habitat;
	}
private:

};

int main()
{
	int size = 4;

	animal** a = new animal*[size];

	a[0] = new cat("Tac", 12, "USA");
	a[1] = new dog("God", 15, "Russia");
	a[2] = new tiger("Regit", 3, "USA");
	a[3] = new hyena("Aneyh", 2, "Russia");

	for (int i = 0; i < size; ++i)
	{
		a[i]->print(cout);
		cout << '\n';
	}

	for (int i = 0; i < size; ++i)
	{
		delete a[i];
	}

	delete[] a;
}