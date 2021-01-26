#include <map>
#include <iostream>
#include <functional>
#include <string>
#include <windows.h>

using namespace std;

template<class key, class value>
bool find_value(const map<key, value>& m, const value& v, key& result)
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
bool find_key(const map<key, value>& m, const key& k, value& result)
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

//узел
template<class T>
class Node
{
protected:
	//закрытые переменные Node N; N.data = 10 вызовет ошибку
	T data;
	//не можем хранить Node, но имеем право хранить указатель
	Node* left;
	Node* right;
	Node* parent;
	//переменная, необходимая для поддержания баланса дерева
	int height;
public:
	//доступные извне переменные и функции
	virtual void setData(T d) { data = d; }
	virtual T getData() { return data; }
	int getHeight() { return height; }
	virtual Node* getLeft() { return left; }
	virtual Node* getRight() { return right; }
	virtual Node* getParent() { return parent; }
	virtual void setLeft(Node* N) { left = N; }
	virtual void setRight(Node* N) { right = N; }
	virtual void setParent(Node* N) { parent = N; }
	//Конструктор. Устанавливаем стартовые значения для указателей
	Node<T>(T n)
	{
		data = n;
		left = right = parent = NULL;
		height = 1;
	}
	Node<T>()
	{
		left = NULL;
		right = NULL;
		parent = NULL;
		height = 1;
	}
	virtual void print()
	{
		cout << "\n" << data;
	}
	virtual void setHeight(int h)
	{
		height = h;
	}
	template<class T> friend ostream& operator<< (ostream& stream, Node<T>& N);
};
template<class T>
ostream& operator<< (ostream& stream, Node<T>& N)
{
	stream << "\nNode data: " << N.data << ", height: " << N.height;
	return stream;
}

template<class T>
void print(Node<T>* N) { cout << "\n" << N->getData(); }

template<class T>
class Tree
{
protected:
	//корень - его достаточно для хранения всего дерева
	Node<T>* root;
public:
	//доступ к корневому элементу
	virtual Node<T>* getRoot() { return root; }
	//конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит в никуда
	Tree<T>() { root = NULL; }
	//рекуррентная функция добавления узла. Устроена аналогично, но вызывает сама себя - добавление в левое или правое поддерево
	virtual Node<T>* Add_R(Node<T>* N)
	{
		return Add_R(N, root);
	}
	virtual Node<T>* Add_R(Node<T>* N, Node<T>* Current)
	{
		if (N == NULL) return NULL;
		if (root == NULL)
		{
			root = N;
			return N;
		}
		if (Current->getData() > N->getData())
		{
			//идем влево
			if (Current->getLeft() != NULL)
				Current->setLeft(Add_R(N, Current->getLeft()));
			else
				Current->setLeft(N);
			Current->getLeft()->setParent(Current);
		}
		if (Current->getData() < N->getData())
		{
			//идем вправо
			if (Current->getRight() != NULL)
				Current->setRight(Add_R(N, Current->getRight()));
			else
				Current->setRight(N);
			Current->getRight()->setParent(Current);
		}
		if (Current->getData() == N->getData())
			//нашли совпадение
			;
		//для несбалансированного дерева поиска
		return Current;
	}
	//функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
	virtual void Add(T n)
	{
		Node<T>* N = new Node<T>;
		N->setData(n);
		Add_R(N);
	}
	virtual Node<T>* Min(Node<T>* Current = NULL)
	{
		//минимум - это самый "левый" узел. Идём по дереву всегда влево
		if (root == NULL) return NULL;
		if (Current == NULL)
			Current = root;
		while (Current->getLeft() != NULL)
			Current = Current->getLeft();
		return Current;
	}
	virtual Node<T>* Max(Node<T>* Current = NULL)
	{
		//минимум - это самый "правый" узел. Идём по дереву всегда вправо
		if (root == NULL) return NULL;
		if (Current == NULL)
			Current = root;
		while (Current->getRight() != NULL)
			Current = Current->getRight();
		return Current;
	}
	//поиск узла в дереве. Второй параметр - в каком поддереве искать, первый - что искать
	virtual Node<T>* Find(T data, Node<T>* Current)
	{
		//база рекурсии
		if (Current == NULL) return NULL;
		if (Current->getData() == data) return Current;
		//рекурсивный вызов
		if (Current->getData() > data) return Find(data, Current->getLeft());
		if (Current->getData() < data) return Find(data, Current->getRight());
	}
	//три обхода дерева
	virtual void PreOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL)
			f(N);
		if (N != NULL && N->getLeft() != NULL)
			PreOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PreOrder(N->getRight(), f);
	}
	//InOrder-обход даст отсортированную последовательность
	virtual void InOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL && N->getLeft() != NULL)
			InOrder(N->getLeft(), f);
		if (N != NULL)
			f(N);
		if (N != NULL && N->getRight() != NULL)
			InOrder(N->getRight(), f);
	}
	virtual void PostOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL && N->getLeft() != NULL)
			PostOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PostOrder(N->getRight(), f);
		if (N != NULL)
			f(N);
	}
};

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
		return b1.m_bookTitle < b2.m_bookTitle;
	}

	friend bool operator>(const book& b1, const book& b2)
	{
		return b1.m_bookTitle > b2.m_bookTitle;
	}

	friend bool operator==(const book& b1, const book& b2)
	{
		return b1.m_bookTitle == b2.m_bookTitle;
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
class NodeHeap
{
private:
	T value;
public:
	//установить данные в узле
	T getValue() { return value; }
	void setValue(T v) { value = v; }
	//сравнение узлов
	int operator<(NodeHeap N)
	{
		return (value < N.getValue());
	}
	int operator>(NodeHeap N)
	{
		return (value > N.getValue());
	}
	//вывод содержимого одного узла
	void print()
	{
		cout << value;
	}
};
template <class T>
void print(NodeHeap<T>* N)
{
	cout << N->getValue() << "\n";
}

//куча (heap)
template <class T>
class Heap
{
private:
	//массив
	NodeHeap<T>* arr;
	//сколько элементов добавлено
	int len;
	//сколько памяти выделено
	int size;
public:
	// TODO
	NodeHeap<T>* ExtractMax()
	{

	}
	//доступ к вспомогательным полям кучи и оператор индекса
	int getCapacity() { return size; }
	int getCount() { return len; }
	NodeHeap<T>& operator[](int index)
	{
		if (index < 0 || index >= len)
			;//?
		return arr[index];
	}
	//конструктор
	Heap<T>(int MemorySize = 100)
	{
		arr = new NodeHeap<T>[MemorySize];
		len = 0;
		size = MemorySize;
	}
	//поменять местами элементы arr[index1], arr[index2]
	void Swap(int index1, int index2)
	{
		if (index1 <= 0 || index1 >= len)
			;
		if (index2 <= 0 || index2 >= len)
			;
		//здесь нужна защита от дурака
		NodeHeap<T> temp;
		temp = arr[index1];
		arr[index1] = arr[index2];
		arr[index2] = temp;
	}
	//скопировать данные между двумя узлами
	void Copy(NodeHeap<T>* dest, NodeHeap<T>* source)
	{
		dest->setValue(source->getValue());
	}
	//функции получения левого, правого дочернего элемента, родителя или их индексов в массиве
	NodeHeap<T>* GetLeftChild(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//здесь нужна защита от дурака
		return &arr[index * 2 + 1];
	}
	NodeHeap<T>* GetRightChild(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//здесь нужна защита от дурака
		return &arr[index * 2 + 2];
	}
	NodeHeap<T>* GetParent(int index)
	{
		if (index <= 0 || index >= len)
			;
		//здесь нужна защита от дурака
		if (index % 2 == 0)
			return &arr[index / 2 - 1];
		return &arr[index / 2];
	}
	int GetLeftChildIndex(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//здесь нужна защита от дурака
		return index * 2 + 1;
	}
	int GetRightChildIndex(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//здесь нужна защита от дурака
		return index * 2 + 2;
	}
	int GetParentIndex(int index)
	{
		if (index <= 0 || index >= len)
			;
		//здесь нужна защита от дурака
		if (index % 2 == 0)
			return index / 2 - 1;
		return index / 2;
	}
	//просеить элемент вверх
	void SiftUp(int index = -1)
	{
		if (index == -1) index = len - 1;
		int parent = GetParentIndex(index);
		int index2 = GetLeftChildIndex(parent);
		if (index2 == index) index2 = GetRightChildIndex(parent);
		int max_index = index;
		if (index < len && index2 < len && parent >= 0)
		{
			if (arr[index] > arr[index2])
				max_index = index;
			if (arr[index] < arr[index2])
				max_index = index2;
		}
		if (parent < len && parent >= 0 && arr[max_index]>arr[parent])
		{
			//нужно просеивание вверх
			Swap(parent, max_index);
			SiftUp(parent);
		}
	}
	//добавление элемента - вставляем его в конец массива и просеиваем вверх
	template <class T>
	void Add(T v)
	{
		NodeHeap<T>* N = new NodeHeap<T>;
		N->setValue(v);
		Add(N);
	}
	template <class T>
	void Add(NodeHeap<T>* N)
	{
		if (len < size)
		{
			Copy(&arr[len], N);
			len++;
			SiftUp();
		}
	}
	//перечислить элементы кучи и применить к ним функцию
	void Straight(void(*f)(NodeHeap<T>*))
	{
		int i;
		for (i = 0; i < len; i++)
		{
			f(&arr[i]);
		}
	}
	//перебор элементов, аналогичный проходам бинарного дерева
	void InOrder(void(*f)(NodeHeap<T>*), int index = 0)
	{
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (index >= 0 && index < len)
			f(&arr[index]);
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
	}
};


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	cout << "Задание 2.1\n";

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

	if (find_key<string, unsigned int>(m, name, circulation))
	{
		cout << "Тираж этой книги: " << circulation << '\n';
	}
	else
	{
		cout << "Такой книги нет!\n";
	}

	cout << "Введите тираж книги: ";
	cin >> circulation;

	if (find_value<string, unsigned int>(m, circulation, name))
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

	cout << "Задание 2.2\n";

	cout << "Задание 2.3\n";

	Tree<book> t;
	
	t.Add(book("Иванов", "Иван", "Лолита", 1500, "Кадокава", 10, book::typeOfPublication::audio, 10000));
	t.Add(book("Иванов", "Сергей", "Книга", 150, "Кадокава", 10, book::typeOfPublication::electronic, 10000));
	t.Add(book("Иванов", "Максим", "Лина", 1, "Кадокава", 10, book::typeOfPublication::paper, 10000));
	t.Add(book("Иванов", "Владислав", "Программа", 100, "Кадокава", 10, book::typeOfPublication::electronic, 10000));
	t.Add(book("Иванов", "Рома", "Панда", 15000, "Кадокава", 10, book::typeOfPublication::audio, 10000));
	t.Add(book("Иванов", "Юля", "Свойства", 1500, "Кадокава", 10, book::typeOfPublication::paper, 10000));

	t.PreOrder(t.getRoot(), [](Node<book>*x)
		{
			cout << *x;
		});

	cout << "\nЗадание 2.4\n";

	Heap<int> Tree;
	Tree.Add(1);
	Tree.Add(-1);
	Tree.Add(-2);
	Tree.Add(2);
	Tree.Add(5);
	Tree.Add(6);
	Tree.Add(-3);
	Tree.Add(-4);
	Tree.Add(4);
	Tree.Add(3);
	cout << "\n-----\nStraight:";
	void(*f_ptr)(NodeHeap<int>*); f_ptr = print;
	Tree.Straight(f_ptr);
}