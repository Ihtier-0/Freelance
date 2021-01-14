#include <iostream>
#include <exception>
#include <list>

using namespace std;

class ContainerException : public exception
{
public:
	ContainerException(const string& error)
		: m_error(error) {}
	const char* what() const noexcept { return m_error.c_str(); }
private:
	string m_error;
};

class Container
{
public:
	void pushFront(const int_least64_t& v)
	{
		c.push_front(v);
	}

	void pushBack(const int_least64_t& v)
	{
		c.push_back(v);
	}

	int_least64_t getFront()
	{
		if (c.size() == 0)
		{
			throw ContainerException("Empty on getFront()");
		}

		return c.front();
	}

	int_least64_t getBack()
	{
		if (c.size() == 0)
		{
			throw ContainerException("Empty on getBack()");
		}

		return c.back();
	}

	int_least64_t getAverage()
	{
		int size = c.size();
		if (c.size() == 0)
		{
			throw ContainerException("Empty on getAverage()");
		}

		double sum = 0;

		for (int_least64_t e : c)
		{
			sum += e;
		}

		return sum / size;
	}

	int_least64_t popFront()
	{
		if (c.size() == 0)
		{
			throw ContainerException("Empty on popFront()");
		}

		int_least64_t result = c.front();
		c.pop_front();
		return result;
	}

	int_least64_t popBack()
	{
		if (c.size() == 0)
		{
			throw ContainerException("Empty on popBack()");
		}

		int_least64_t result = c.back();
		c.pop_back();
		return result;
	}

private:
	list<int_least64_t> c;
};

int main()
{
	char c;
	int_least64_t v;
	Container mc;
	while (cin >> c)
	{
		try
		{
			switch (c)
			{
			case 'f':
				cout << mc.getFront() << "\n";
				break;
			case 'b':
				cout << mc.getBack() << "\n";
				break;
			case 'h':
				cin >> v;
				mc.pushFront(v);
				break;
			case 't':
				cin >> v;
				mc.pushBack(v);
				break;
			case 'a':
				cout << mc.getAverage() << "\n";
				break;
			case 'y':
				cout << mc.popFront() << "\n";
				break;
			case 'z':
				cout << mc.popBack() << "\n";
				break;
			}
		}
		catch (const std::exception& e)
		{
			cout << e.what() << "\n";
		}
		catch (...)
		{
			cout << "Dead case\n";
		}
	}
	return 0;
}