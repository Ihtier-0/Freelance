#include <iostream>
#include <exception>
#include <vector>
#include <algorithm>

using namespace std;

class PriorityQueue2MinException : public exception
{
public:
	PriorityQueue2MinException(const std::string& error)
		: m_error(error) {}

	const char* what() const noexcept override
	{
		return m_error.c_str();
	}
private:
	std::string m_error;
};

class PriorityQueue2Min
{
public:
	void insert(const int_least64_t& v)
	{
		q.push_back(v);
	}
	int_least64_t extractMin()
	{
		std::vector<int_least64_t>::iterator result = min_element(q.begin(), q.end());
		int_least64_t value = *result;

		q.erase(result);

		return value;
	}
	int_least64_t firstMin()
	{
		int size = q.size();

		if(size == 0)
		{
			throw PriorityQueue2MinException("Empty on firstMin()");
		}

		return *min_element(q.begin(), q.end());
	}
	int_least64_t secondMin()
	{
		int size = q.size();

		if (size == 0 || size == 1)
		{
			throw PriorityQueue2MinException("Empty on secondMin()");
		}

		int_least64_t firstMin = this->firstMin(), secondMin = q[0];

		for (int i = 1; i < size; ++i)
		{
			if (q[i] > firstMin && secondMin > q[i])
			{
				secondMin = q[i];
			}
		}

		return secondMin;
	}
private:
	vector<int_least64_t> q;
};

int main()
{
	char c;
	int_least64_t v;
	PriorityQueue2Min mpq;
	while (cin >> c)
	{
		try
		{
			switch (c)
			{
			case 'f':
				cout << mpq.firstMin() << "\n";
				break;
			case 's':
				cout << mpq.secondMin() << "\n";
				break;
			case 'a':
				cin >> v;
				mpq.insert(v);
				break;
			case 'p':
				cout << mpq.extractMin() << "\n";
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
