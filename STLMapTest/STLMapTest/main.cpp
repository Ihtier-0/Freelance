#include <map>
#include <iostream>
#include <functional>
#include <string>
#include <windows.h>

using namespace std;

template<class key, class value>
bool find_key(const map<key, value>& m, const value& v, key& result)
{
	auto it_m = m.begin();

	while (it_m != m.end())
	{
		if (it_m->second == v)
		{
			result = it_m->first;
			return true;
		}
		it_m++;
	}

	return false;
}

template<class key, class value>
bool find_value(const map<key, value>& m, const key& k, value& result)
{
	auto it_m = m.begin();

	while (it_m != m.end())
	{
		if (it_m->first == k)
		{
			result = it_m->second;
			return true;
		}
		it_m++;
	}

	return false;
}

template<class key, class value>
map<key, value> filter(const map<key, value>& m, const function<bool(pair<key, value>)>& f)
{
	auto it_m = m.begin();

	map<key, value> result;

	while (it_m != m.end())
	{
		if (f(*it_m))
		{
			result[it_m->first] = it_m->second;
		}
		it_m++;
	}

	return result;
}

template<class key, class value>
void print(const map<key, value>& m)
{
	auto it_m = m.begin();

	while (it_m != m.end())
	{
		cout << "Название книги: " << it_m->first << ", тираж: " << it_m->second << "\n";
		it_m++;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	map<string, unsigned int> m;

	m["Десять негритят"] = 400;
	m["Лолита"] = 500000;
	m["Гарри Поттер"] = 4000;
	m["Маленький принц"] = 5000;
	m["Дон Кихот"] = 300;
	m["Красная книга"] = 40;
	m["Библия"] = 5;

	cout << "Книги:\n";
	print(m);

	string name;
	unsigned int circulation;
	cout << "Введите название книги: ";
	getline(cin, name);

	if (find_value<string, unsigned int>(m, name, circulation))
	{
		cout << "Тираж этой книги: " << circulation << '\n';
	}
	else
	{
		cout << "Такой книги нет!\n";
	}

	cout << "Введите тираж книги: ";
	cin >> circulation;

	if (find_key<string, unsigned int>(m, circulation, name))
	{
		cout << "Название книги с таким тиражом: " << name << '\n';
	}
	else
	{
		cout << "Книги с таким тиражом нет!\n";
	}

	// больше чем 1000 экземпляров
	function<bool(pair<string, unsigned int>)> f = [](const pair<string, unsigned int>& x) -> bool
	{
		return x.second > 1000;
	};

	cout << "Книги у которых больше, чем 1000 экземлпяров:\n";
	print(filter(m, f));
}