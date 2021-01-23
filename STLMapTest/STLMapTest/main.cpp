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
		cout << "�������� �����: " << it_m->first << ", �����: " << it_m->second << "\n";
		it_m++;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	map<string, unsigned int> m;

	m["������ ��������"] = 400;
	m["������"] = 500000;
	m["����� ������"] = 4000;
	m["��������� �����"] = 5000;
	m["��� �����"] = 300;
	m["������� �����"] = 40;
	m["������"] = 5;

	cout << "�����:\n";
	print(m);

	string name;
	unsigned int circulation;
	cout << "������� �������� �����: ";
	getline(cin, name);

	if (find_value<string, unsigned int>(m, name, circulation))
	{
		cout << "����� ���� �����: " << circulation << '\n';
	}
	else
	{
		cout << "����� ����� ���!\n";
	}

	cout << "������� ����� �����: ";
	cin >> circulation;

	if (find_key<string, unsigned int>(m, circulation, name))
	{
		cout << "�������� ����� � ����� �������: " << name << '\n';
	}
	else
	{
		cout << "����� � ����� ������� ���!\n";
	}

	// ������ ��� 1000 �����������
	function<bool(pair<string, unsigned int>)> f = [](const pair<string, unsigned int>& x) -> bool
	{
		return x.second > 1000;
	};

	cout << "����� � ������� ������, ��� 1000 �����������:\n";
	print(filter(m, f));
}