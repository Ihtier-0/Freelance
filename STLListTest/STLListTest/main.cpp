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

class book
{
public:
	enum typeOfPublication
	{
		electronic, paper, audio, unknown
	};

public:
	book() : m_authorsSurname(), m_authorsName(),
		m_bookTitle(), m_yearOfPublishing(-1),
		m_publisherName(), m_numberOfPages(-1),
		m_type(typeOfPublication::unknown), m_circulation(-1) {}

	book(const string& a_authorsSurname,
		const string& a_authorsName,
		const string& a_bookTitle,
		const int& a_yearOfPublishing,
		const string& a_publisherName,
		const int& a_numberOfPages,
		const typeOfPublication& a_type,
		const int& a_circulation) : m_authorsName(a_authorsName), m_authorsSurname(a_authorsSurname),
		m_bookTitle(a_bookTitle), m_yearOfPublishing(a_yearOfPublishing), m_publisherName(a_publisherName),
		m_numberOfPages(a_numberOfPages), m_type(a_type), m_circulation(a_circulation) {}

	friend ostream& operator<<(ostream& out, const book& b)
	{
		out << b.m_authorsSurname << ' ' << b.m_authorsName << ' ' << b.m_bookTitle << ' ' << b.m_yearOfPublishing << ' '
			<< b.m_publisherName << ' ' << b.m_numberOfPages << ' ';

		switch (b.m_type)
		{
		case typeOfPublication::electronic:
		{
			out << "electronic";
			break;
		}
		case typeOfPublication::paper:
		{
			out << "paper";
			break;
		}
		case typeOfPublication::audio:
		{
			out << "audio";
			break;
		}
		case typeOfPublication::unknown:
		{
			out << "unknown";
			break;
		}
		}

		out << ' ' << b.m_circulation;
	
		return out;
	}

	friend bool operator<(const book& b1, const book& b2)
	{
		return b1.m_circulation < b2.m_circulation ||
			(b1.m_circulation == b2.m_circulation && b1.m_yearOfPublishing < b2.m_yearOfPublishing) ||
			(b1.m_circulation == b2.m_circulation && b1.m_yearOfPublishing == b2.m_yearOfPublishing && b1.m_bookTitle < b2.m_bookTitle);
	}

private:
	string m_authorsSurname;
	string m_authorsName;
	string m_bookTitle;
	int m_yearOfPublishing;
	string m_publisherName;
	int m_numberOfPages;
	typeOfPublication m_type;
	int m_circulation;
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
	//ListIterator(ValueType* p) { ptr = p; }
	ListIterator(Element<ValueType>* p) { ptr = p; }
	ListIterator(const ListIterator& it) { ptr = it.ptr; }
	bool operator!=(ListIterator const& other) const { return ptr != other.ptr; }
	bool operator==(ListIterator const& other) const
	{
		return ptr == other.ptr;
	}//need for BOOST_FOREACH
	Element<ValueType>& operator*()
	{
		return *ptr;
	}
	ListIterator& operator++() { ptr = ptr->getNext(); return *this; }
	ListIterator& operator++(int v) { ptr = ptr->getNext(); return *this; }
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
	ListIterator<T> iterator;
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
			LinkedListParent<T>::tail = new Element<T>(value);
			LinkedListParent<T>::head->setNext(LinkedListParent<T>::tail);
			LinkedListParent<T>::tail->setPrevious(LinkedListParent<T>::head);
			return LinkedListParent<T>::tail;
		}
		else
		{
			LinkedListParent<T>::tail->setNext(new Element<T>(value));
			LinkedListParent<T>::tail->getNext()->setPrevious(LinkedListParent<T>::tail);

			LinkedListParent<T>::tail = LinkedListParent<T>::tail->getNext();

			return LinkedListParent<T>::tail;
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

	while (b != l.end())
	{
		cout << *b << '\n';
		++b;
	}

	if (b != ListIterator<T>())
	{
		cout << *b << ' ';
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Задание 1.1\n";
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

	cout << "Задание 1.2\n";
	list<book> l1;

	push(l1, book("Иванов", "Иван", "Лолита", 1500, "Кадокава", 10, book::typeOfPublication::audio, 10000));
	push(l1, book("Иванов", "Сергей", "Книга", 150, "Кадокава", 10, book::typeOfPublication::electronic, 10000));
	push(l1, book("Иванов", "Максим", "Лина", 1, "Кадокава", 10, book::typeOfPublication::paper, 10000));
	push(l1, book("Иванов", "Владислав", "Программа", 100, "Кадокава", 10, book::typeOfPublication::electronic, 10000));
	push(l1, book("Иванов", "Рома", "Панда", 15000, "Кадокава", 10, book::typeOfPublication::audio, 10000));
	push(l1, book("Иванов", "Юля", "Свойства", 1500, "Кадокава", 10, book::typeOfPublication::paper, 10000));

	print(l1);

	cout << "pop:\n";
	while (!l1.empty())
	{
		cout << pop(l1) << '\n';
	}

	cout << "Задание 1.3\n";

	doubleLinkedList<int> l2;
	l2.push(1);
	l2.push(5);
	l2.push(7);
	l2.push(8);
	l2.push(-1);

	while (l2.Number())
	{
		cout << *(l2.pop()) << ' ';
	}
	cout << '\n';

	cout << "Задание 1.4\n";

	l2.push(1);
	l2.push(5);
	l2.push(7);
	l2.push(8);
	l2.push(-1);
	print(l2);
	cout << '\n';

	cout << "Задание 1.5\n";

	sortDoubleLinkedList<book> l3;

	l3.push(book("Иванов", "Иван", "Лолита", 1500, "Кадокава", 10, book::typeOfPublication::audio, 10000));
	l3.push(book("Иванов", "Сергей", "Книга", 150, "Кадокава", 10, book::typeOfPublication::electronic, 10000));
	l3.push(book("Иванов", "Максим", "Лина", 1, "Кадокава", 10, book::typeOfPublication::paper, 10000));
	l3.push(book("Иванов", "Владислав", "Программа", 100, "Кадокава", 10, book::typeOfPublication::electronic, 10000));
	l3.push(book("Иванов", "Рома", "Панда", 15000, "Кадокава", 10, book::typeOfPublication::audio, 10000));
	l3.push(book("Иванов", "Юля", "Свойства", 1500, "Кадокава", 10, book::typeOfPublication::paper, 10000));

	print(l3);
}