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
		cout << "card number: " << it_m->first << ", patient: " << it_m->second << "\n";
		it_m++;
	}
}

class patient
{
public:
	patient(const string& FullName, const unsigned int& bloodType)
		: m_FullName(FullName), m_bloodType(bloodType) {}
	patient() : m_FullName(), m_bloodType() {}
	string get_FullName() const
	{
		return m_FullName;
	}
	unsigned int get_bloodtype() const
	{
		return m_bloodType;
	}
private:
	string m_FullName;
	unsigned int m_bloodType;

	friend bool operator==(const patient& p1, const patient& p2)
	{
		return p1.m_FullName == p2.m_FullName && p1.m_bloodType == p2.m_bloodType;
	}

	friend ostream& operator<< (ostream& out, const patient& p)
	{
		out << "Full Name: " << p.m_FullName << ", blood type: " << p.m_bloodType;

		return out;
	}
};

int main()
{
	map<unsigned int, patient> m;
	m[123] = patient("Petrov", 2);
	m[124] = patient("Ivanov", 3);
	m[125] = patient("Sidorov", 4);
	m[126] = patient("Nikolaev", 1);
	m[127] = patient("Abramov", 3);
	m[128] = patient("Fedorov", 1);
	m[129] = patient("Kuznetsov", 2);
	cout << "Map:\n";
	print(m);

	patient p;
	unsigned int cardNumber;
	cout << "enter the patient card number you want to find: ";
	cin >> cardNumber;

	if (find_value<unsigned int, patient>(m, cardNumber, p))
	{
		cout << "found patient: " << p << '\n';
	}
	else
	{
		cout << "Not Found!\n";
	}

	std::string fullName;
	unsigned int bloodType;
	cout << "input full name patient: ";
	cin.get();
	getline(cin, fullName);
	cout << "input blood Type patient: ";
	cin >> bloodType;

	if (find_key<unsigned int, patient>(m, patient(fullName, bloodType), cardNumber))
	{
		cout << "card number patient: " << cardNumber << '\n';
	}
	else
	{
		cout << "Not Found!\n";
	}

	// группа крови больше 2
	function<bool(pair<unsigned int, patient>)> f = [](const pair<unsigned int, patient>& x) -> bool
	{
		return x.second.get_bloodtype() > 2;
	};

	cout << "filtered map:\n";
	print(filter(m, f));
}