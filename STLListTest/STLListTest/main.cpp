#include <list>
#include <iostream>
#include <functional>

using namespace std;

template<class T>
void push(list<T>& lst, T element)
{
	auto p = lst.begin();
	
	while (p != lst.end())
	{
		if (*p > element)
		{
			break;
		}
		p++;
	}

	lst.insert(p, element);
}

template<class T>
T pop_back(list<T>& lst)
{
	T back = lst.back();
	
	lst.pop_back();

	return back;
}

template<class T>
list<T> filter(const list<T>& lst, const function<bool(const T&)> &f)
{
	auto p = lst.begin();

	list<T> result;
	
	while (p != lst.end())
	{
		if (f(*p))
		{
			result.push_back(*p);
		}
		p++;
	}

	return result;
}

template<class T>
void print(const list<T>& lst)
{
	auto p = lst.begin();

	list<T> result;

	while (p != lst.end())
	{
		cout << *p << ' ';
		++p;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	list<char> l;

	for (int i = 0; i < 10; ++i)
	{
		push(l, char('A' + i));
	}

	cout << "Полученный список:\n";
	print(l);
	cout << '\n';

	cout << "Только гластные элементы списка:\n";
	function<bool(const char&)> f = [](const char& x) -> bool
	{
		char upX = toupper(x);
		return upX == 'A' || upX == 'E'
			|| upX == 'I' || upX == 'O'
			|| upX == 'U' || upX == 'Y';
	};

	print(filter(l, f));
	cout << '\n';
}