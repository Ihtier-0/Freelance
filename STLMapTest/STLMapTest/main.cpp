#include <map>
#include <iostream>
#include <functional>
#include <string>

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
		cout << "book name: " << it_m->first << ", circulation: " << it_m->second << "\n";
		it_m++;
	}
}

int main()
{
	map<string, unsigned int> m;

	m["Loving"] = 400;
	m["Lolita"] = 500000;
	m["Brave new world"] = 4000;
	m["1984"] = 5000;
	m["Invisible man"] = 300;
	m["Scoop"] = 40;
	m["The Magus"] = 5;

	cout << "Map:\n";
	print(m);

	string name;
	unsigned int circulation;
	cout << "enter book name: ";
	getline(cin, name);

	if (find_value<string, unsigned int>(m, name, circulation))
	{
		cout << "circulation this book: " << circulation << '\n';
	}
	else
	{
		cout << "Not Found!\n";
	}

	cout << "enter book circulation: ";
	cin >> circulation;

	if (find_key<string, unsigned int>(m, circulation, name))
	{
		cout << "name book: " << name << '\n';
	}
	else
	{
		cout << "Not Found!\n";
	}

	// больше чем 1000 экземпл€ров
	function<bool(pair<string, unsigned int>)> f = [](const pair<string, unsigned int>& x) -> bool
	{
		return x.second > 1000;
	};

	cout << "filtered map:\n";
	print(filter(m, f));
}