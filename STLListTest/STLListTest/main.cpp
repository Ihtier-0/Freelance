#include <list>
#include <iostream>
#include <functional>
#include <string>

using namespace std;

template<class T>
void push(list<T>& lst, T element)
{
	auto p = lst.begin();
	
	while (p != lst.end())
	{
		if (*p < element)
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
T pop(list<T>& lst)
{
	T front = lst.front();

	lst.pop_front();

	return front;
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
		cout << *p << '\n';
		++p;
	}
}

class Fraction
{
private:
	int numerator, denominator;
public:
	int Numerator() const
	{
		return numerator;
	}
	int Denominator() const
	{
		return denominator;
	}
	Fraction()
	{
		numerator = 1;
		denominator = 1;
	}
	Fraction(int n, int d)
	{
		numerator = n;
		if (d == 0)
		{
			cout << "ERROR: ATTEMPTING TO DIVIDE BY ZERO" << endl;
			exit(0); // will terminate the program if division by 0 is attempted
		}
		else
		{
			denominator = d;
		}

		//if (n % d == 0 && n >= d)
		//{
		//	numerator /= d;
		//	denominator = 1;
		//}
	}
	friend Fraction operator+(const Fraction& left, const Fraction& right)
	{
		int n = left.numerator * right.denominator + right.numerator * left.denominator;
		int d = left.denominator * right.denominator;
		return Fraction(n / Fraction::gcd(n, d), d / Fraction::gcd(n, d));
	}
	friend Fraction operator-(const Fraction& left, const Fraction& right)
	{
		int n = left.numerator * right.denominator - right.numerator * left.denominator;
		int d = left.denominator * right.denominator;
		return Fraction(n / Fraction::gcd(n, d), d / Fraction::gcd(n, d));
	}
	friend Fraction operator*(const Fraction& left, const Fraction& right)
	{
		int n = left.numerator * right.numerator;
		int d = left.denominator * right.denominator;
		return Fraction(n / Fraction::gcd(n, d), d / Fraction::gcd(n, d));
	}
	friend Fraction operator/(const Fraction& left, const Fraction& right)
	{
		int n = left.numerator * right.denominator;
		int d = left.denominator * right.numerator;
		return Fraction(n / Fraction::gcd(n, d), d / Fraction::gcd(n, d));
	}
	static int gcd(int n, int d)
	{
		int remainder;
		while (d != 0)
		{
			remainder = n % d;
			n = d;
			d = remainder;
		}
		return n;
	}
	friend ostream& operator<<(ostream &out, const Fraction& f)
	{
		if (f.denominator == 1) // e.g. fraction 2/1 will display simply as 2
			out << f.numerator;
		else if (f.numerator == 0)
			out << 0;
		else
			out << f.numerator << "/" << f.denominator;

		return out;
	}

	friend bool operator<(const Fraction& left, const Fraction& right)
	{
		if (left.denominator == right.denominator)
		{
			return left.numerator < right.numerator;
		}
		else
		{
			return left.numerator * right.denominator < right.numerator * left.denominator;
		}
	}
	friend bool operator==(const Fraction& left, const Fraction& right)
	{
		return left.numerator == right.numerator && left.denominator == right.denominator;
	}
};

class Airline
{
public:
	Airline() : m_name(), m_international_code(0), m_number_of_served_lines(0), m_country(), m_internet_site_address(),
		m_rating_reliability(0) {}
	Airline(string a_name,
	int a_international_code,
	int a_number_of_served_lines,
	string a_country,
	string a_internet_site_address,
	int a_rating_reliability) : m_name(a_name), m_international_code(a_international_code),
		m_number_of_served_lines(a_number_of_served_lines), m_country(a_country), m_internet_site_address(a_internet_site_address),
		m_rating_reliability(a_rating_reliability) {}

	friend ostream& operator<<(ostream& out, const Airline& a)
	{
		out << a.m_name << ' ' << a.m_international_code << ' ' << a.m_number_of_served_lines << ' '
			<< a.m_country << ' ' << a.m_internet_site_address << ' ' << a.m_rating_reliability;

		return out;
	}

	friend bool operator<(const Airline& left, const Airline& right)
	{
		return left.m_rating_reliability < right.m_rating_reliability ||
			(left.m_rating_reliability == right.m_rating_reliability &&
				left.m_number_of_served_lines < right.m_number_of_served_lines) ||
			(left.m_rating_reliability == right.m_rating_reliability &&
				left.m_number_of_served_lines == right.m_number_of_served_lines &&
				left.m_name < right.m_name);
	}
private:
	string m_name;
	int m_international_code;
	int m_number_of_served_lines;
	string m_country;
	string m_internet_site_address;
	int m_rating_reliability;
};

template <class T>
class Element
{
	//элемент связного списка
private:
	//указатель на предыдущий и следующий элемент
	Element* next;
	Element* prev;
	//информация, хранимая в поле
	T field;
public:
	Element(T value = 0, Element<T>* next_ptr = NULL, Element<T>* prev_ptr = NULL)
	{
		field = value;
		next = next_ptr;
		prev - prev_ptr;
	}
	//доступ к полю *next
	virtual Element* getNext() { return next; }
	virtual void setNext(Element* value) { next = value; }
	//доступ к полю *prev
	virtual Element* getPrevious() { return prev; }
	virtual void setPrevious(Element* value) { prev = value; }
	//доступ к полю с хранимой информацией field
	virtual T getValue() { return field; }
	virtual void setValue(T value) { field = value; }
	template<class T> friend ostream& operator<< (ostream& ustream, Element<T>& obj);
};

template<class T>
ostream& operator << (ostream& ustream, Element<T>& obj)
{
	ustream << obj.field;
	return ustream;
}

template <class T>
class LinkedListParent
{
protected:
	//достаточно хранить начало и конец
	Element<T>* head;
	Element<T>* tail;
	//для удобства храним количество элементов
	int num;
public:
	virtual int Number() { return num; }
	virtual Element<T>* getBegin() { return head; }
	virtual Element<T>* getEnd() { return tail; }
	LinkedListParent()
	{
		//конструктор без параметров
		cout << "\nParent constructor";
		head = NULL;
		tail = NULL;
		num = 0;
	}
	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать добавление
		virtual Element<T>* push(T value) = 0;
	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать удаление
		virtual Element<T>* pop() = 0;
	virtual ~LinkedListParent()
	{
		//деструктор - освобождение памяти
		cout << "\nParent destructor";
	}
	//получение элемента по индексу - какова асимптотическая оценка этого действия?
	virtual Element<T>* operator[](int i)
	{
		//индексация
		if (i < 0 || i > num)
		{
			return NULL;
		}
		int k = 0;
		//ищем i-й элемент - вставем в начало и отсчитываем i шагов вперед
		Element<T>* cur = head;
		for (k = 0; k < i; k++)
		{
			cur = cur->getNext();
		}
		return cur;
	}
	template<class T> friend ostream& operator<< (ostream& ustream,
		LinkedListParent<T>& obj);
	template<class T> friend istream& operator>> (istream& ustream,
		LinkedListParent<T>& obj);
};
template<class T>
ostream& operator << (ostream& ustream, LinkedListParent<T>& obj)
{
	if (typeid(ustream).name() == typeid(ofstream).name())
	{
		ustream << obj.num << "\n";
		for (Element<T>* current = obj.getBegin(); current != NULL; current =
			current->getNext())
			ustream << current->getValue() << " ";
		return ustream;
	}
	ustream << "\nLength: " << obj.num << "\n";
	int i = 0;
	for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext(), i++)
	{
		ustream << "arr[" << i << "] = " << current->getValue() << "\n";
	}
	return ustream;
}
template<class T>
istream& operator >> (istream& ustream, LinkedListParent<T>& obj)
{
	//чтение из файла и консоли совпадают
	int len;
	ustream >> len;
	//здесь надо очистить память под obj, установить obj.num = 0
	double v = 0;
	for (int i = 0; i < len; i++)
	{
		ustream >> v;
		obj.push(v);
	}
	return ustream;
}
template<typename ValueType>
class ListIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
private:
public:
	ListIterator() { ptr = NULL; }
	
	ListIterator(Element<ValueType>* p) { ptr = p; }
	ListIterator(const ListIterator& it) { ptr = it.ptr; }
	bool operator!=(ListIterator const& other) const { return ptr != other.ptr; }
	bool operator==(ListIterator const& other) const
	{
		return ptr == other.ptr;
	}
	Element<ValueType>& operator*()
	{
		return *ptr;
	}
	operator bool() { return ptr; }
	ListIterator& operator++() { if(ptr) ptr = ptr->getNext(); return *this; }
	ListIterator& operator++(int v) { if (ptr) ptr = ptr->getNext(); return *this; }
	ListIterator& operator--() { if (ptr) ptr = ptr->getPrevious(); return *this; }
	ListIterator& operator--(int v) { if (ptr) ptr = ptr->getPrevious(); return *this; }
	ListIterator& operator=(const ListIterator& it) { ptr = it.ptr; return *this; }
	ListIterator& operator=(Element<ValueType>* p) { ptr = p; return *this; }
private:
	Element<ValueType>* ptr;
};

template <class T>
class IteratedLinkedList : public LinkedListParent<T>
{
public:
	IteratedLinkedList() : LinkedListParent<T>()
	{
		cout << "\nIteratedLinkedList constructor\n";
	}
	virtual ~IteratedLinkedList() { cout << "\nIteratedLinkedList destructor\n"; }

	ListIterator<T> begin()
	{
		ListIterator<T> it = LinkedListParent<T>::head; return it;
	}
	ListIterator<T> end() {
		ListIterator<T> it = LinkedListParent<T>::tail; return it;
	}
};

// Очередь
template <class T>
class doubleLinkedList : public IteratedLinkedList<T>
{
public:
	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать добавление
	virtual Element<T>* push(T value)
	{
		LinkedListParent<T>::num++;

		if (!LinkedListParent<T>::head)
		{
			LinkedListParent<T>::head = new Element<T>(value);
			return LinkedListParent<T>::head;
		}
		else if(!LinkedListParent<T>::tail)
		{
			LinkedListParent<T>::tail = LinkedListParent<T>::head;
			LinkedListParent<T>::head = new Element<T>(value, LinkedListParent<T>::tail);
			LinkedListParent<T>::tail->setPrevious(LinkedListParent<T>::head);
			return LinkedListParent<T>::tail;
		}
		else
		{
			LinkedListParent<T>::head = new Element<T>(value, LinkedListParent<T>::head);
			LinkedListParent<T>::head->getNext()->setPrevious(LinkedListParent<T>::head);

			LinkedListParent<T>::tail = LinkedListParent<T>::tail->getNext();

			return LinkedListParent<T>::head;
		}
	}
	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать удаление
	virtual Element<T>* pop()
	{
		LinkedListParent<T>::num--;

		if (LinkedListParent<T>::head)
		{
			Element<T> *tmp = LinkedListParent<T>::head;
			
			LinkedListParent<T>::head = LinkedListParent<T>::head->getNext();

			if (LinkedListParent<T>::head)
			{
				LinkedListParent<T>::head->setPrevious(NULL);
			}
			else
			{
				LinkedListParent<T>::head = NULL;
				LinkedListParent<T>::tail = NULL;
			}

			tmp->setNext(NULL);
			tmp->setPrevious(NULL);

			return tmp;
		}
	}
private:

};

template <class T>
class sortDoubleLinkedList : public IteratedLinkedList<T>
{
public:
	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать добавление
	virtual Element<T>* push(T value)
	{
		LinkedListParent<T>::num++;

		if (!LinkedListParent<T>::head)
		{
			LinkedListParent<T>::head = new Element<T>(value);
			return LinkedListParent<T>::head;
		}
		else if (!LinkedListParent<T>::tail)
		{
			if (!(LinkedListParent<T>::head->getValue() < value))
			{
				LinkedListParent<T>::tail = new Element<T>(value);
				LinkedListParent<T>::head->setNext(LinkedListParent<T>::tail);
				LinkedListParent<T>::tail->setPrevious(LinkedListParent<T>::head);
				return LinkedListParent<T>::tail;
			}
			else
			{
				LinkedListParent<T>::head->setPrevious(new Element<T>(value));
				LinkedListParent<T>::tail = LinkedListParent<T>::head;
				LinkedListParent<T>::head = LinkedListParent<T>::head->getPrevious();
				LinkedListParent<T>::head->setNext(LinkedListParent<T>::tail);
				LinkedListParent<T>::tail->setPrevious(LinkedListParent<T>::head);

				return LinkedListParent<T>::head;
			}
		}
		else if ((LinkedListParent<T>::head->getValue() < value))
		{
			Element<T>* add = new Element<T>(value);
			add->setNext(LinkedListParent<T>::head);
			LinkedListParent<T>::head->setPrevious(add);

			LinkedListParent<T>::head = add;
		}
		else
		{
			Element<T>* tmp = LinkedListParent<T>::head;

			while (tmp && !(tmp->getValue() < value))
			{
				tmp = tmp->getNext();
			}

			Element<T>* add = new Element<T>(value);

			if (tmp)
			{
				add->setNext(tmp->getNext());
				tmp->setNext(add);
				tmp->getNext()->setPrevious(add);
				add->setPrevious(tmp);
			}
			else
			{
				LinkedListParent<T>::tail->setNext(add);
				add->setPrevious(LinkedListParent<T>::tail);

				LinkedListParent<T>::tail = add;
			}

			return LinkedListParent<T>::tail;
		}
	}
	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать удаление
	virtual Element<T>* pop()
	{
		LinkedListParent<T>::num--;

		if (LinkedListParent<T>::head)
		{
			Element<T>* tmp = LinkedListParent<T>::head;

			LinkedListParent<T>::head = LinkedListParent<T>::head->getNext();

			if (LinkedListParent<T>::head)
			{
				LinkedListParent<T>::head->setPrevious(NULL);
			}
			else
			{
				LinkedListParent<T>::head = NULL;
				LinkedListParent<T>::tail = NULL;
			}

			tmp->setNext(NULL);
			tmp->setPrevious(NULL);

			return tmp;
		}
	}
private:

};

template<class T>
void print(IteratedLinkedList<T> &l)
{
	ListIterator<T> b = l.begin();

	while (b)
	{
		cout << *b << '\n';
		++b;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Вариант 6\n";
	cout << "Задание 1.1\n";
	list<Fraction> l;

	for (int i = 0; i < 10; ++i)
	{
		push(l, Fraction(rand()%10, rand()%10));
	}

	cout << "Полученный список:\n";
	print(l);
	cout << '\n';

	cout << "Только правильные дроби:\n";
	function<bool(const Fraction&)> f = [](const Fraction& x) -> bool
	{
		return x.Numerator() < x.Denominator();
	};

	print(filter(l, f));
	cout << '\n';

	cout << "Задание 1.2\n";
	list<Airline> l1;

	push(l1, Airline("saf", 12, 1, "Россия","https::/", 10));
	push(l1, Airline("haaah", 13, 8, "США", "https::/", 1));
	push(l1, Airline("ahhah", 14, 1, "Япония", "https::/", 5));
	push(l1, Airline("qyqyeuq", 15, 4, "Китай", "https::/", 7));
	push(l1, Airline("ahasah", 16, 10, "США", "https::/", -5));
	push(l1, Airline("ashashah ", 17, 7, "Россия", "https::/", -10));

	print(l1);

	cout << "pop:\n";
	while (!l1.empty())
	{
		cout << pop(l1) << '\n';
	}

	cout << "Задание 1.3\n";

	doubleLinkedList<int> l2;
	l2.push(2);
	l2.push(8);
	l2.push(10);
	l2.push(15);
	l2.push(-16);

	while (l2.Number())
	{
		cout << *(l2.pop()) << ' ';
	}
	cout << '\n';

	cout << "Задание 1.4\n";

	l2.push(2);
	l2.push(8);
	l2.push(10);
	l2.push(15);
	l2.push(-16);
	print(l2);
	cout << '\n';

	cout << "Задание 1.5\n";

	sortDoubleLinkedList<Airline> l3;

	l3.push(Airline("saf", 12, 1, "Россия","https::/", 10));
	l3.push(Airline("haaah", 13, 8, "США", "https::/", 1));
	l3.push(Airline("ahhah", 14, 1, "Япония", "https::/", 5));
	l3.push(Airline("qyqyeuq", 15, 4, "Китай", "https::/", 7));
	l3.push(Airline("ahasah", 16, 10, "США", "https::/", -5));
	l3.push(Airline("ashashah ", 17, 7, "Россия", "https::/", -10));

	print(l3);
}