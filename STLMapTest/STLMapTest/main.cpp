#include <map>
#include <iostream>
#include <functional>
#include <string>
#include <windows.h>
#include <queue>

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
	auto it_m = m.find(k);

	if (it_m != m.end())
	{
		result = it_m->second;
		return true;
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
		cout << "Международный код: " << it_m->first << ", количество обслуживаемых линий: " << it_m->second << "\n";
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

	friend bool operator>(const Airline& left, const Airline& right)
	{
		return left.m_rating_reliability > right.m_rating_reliability ||
			(left.m_rating_reliability == right.m_rating_reliability &&
				left.m_number_of_served_lines > right.m_number_of_served_lines) ||
			(left.m_rating_reliability == right.m_rating_reliability &&
				left.m_number_of_served_lines == right.m_number_of_served_lines &&
				left.m_name > right.m_name);
	}

	friend bool operator==(const Airline& left, const Airline& right)
	{
		return left.m_name == right.m_name &&
			left.m_international_code == right.m_international_code &&
			left.m_number_of_served_lines == right.m_number_of_served_lines &&
			right.m_country == left.m_country &&
			left.m_international_code == right.m_international_code && 
			left.m_rating_reliability == right.m_rating_reliability;
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
	NodeHeap<T> ExtractMax()
	{
		if (len != 0)
		{
			NodeHeap<T> result = arr[0];

			for (int i = 1; i < len; ++i)
			{
				arr[i - 1] = arr[i];
			}

			len--;

			return result;
		}
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
			InOrder(f, GetLeftChildIndex(index));
		if (index >= 0 && index < len)
			f(&arr[index]);
		if (GetRightChildIndex(index) < len)
			InOrder(f, GetRightChildIndex(index));
	}
};

template<typename T>
void print_queue(T& q)
{
	while (!q.empty())
	{
		cout << q.top() << '\n';
		q.pop();
	}
	std::cout << '\n';
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	cout << "Задание 2.1\n\n";
	{
		map<int, int> m;

		m[1] = 1;
		m[2] = 15;
		m[3] = 6;
		m[4] = 7;
		m[5] = 8;
		m[6] = 40;
		m[7] = 5;

		cout << "Авиакомпании:\n";
		print(m);

		int code;
		int lines;
		cout << "Введите международный код авиакомпании: ";
		cin >> code;

		if (find_key<int, int>(m, code, lines))
		{
			cout << "Количество обслуживаемых линий: " << lines << '\n';
		}
		else
		{
			cout << "Такой авиакомпани нет!\n";
		}

		cout << "Введите количество обслуживаемых линий авиакомпании: ";
		cin >> lines;

		if (find_value<int, int>(m, lines, code))
		{
			cout << "Международный код авиакомпании с таким количеством линий: " << code << '\n';
		}
		else
		{
			cout << "Такой авиакомпании нет!\n";
		}

		function<bool(pair<int, int>)> f = [](const pair<int, int>& x) -> bool
		{
			return x.first > 5;
		};

		cout << "Авиакомпании с международным кодом больше 5:\n";
		print(filter(m, f));
	}
	cout << "\nЗадание 2.2\n\n";
	{
		std::priority_queue < Airline > q;
		q.push(Airline("saf", 12, 1, "Россия", "https::/", 10));
		q.push(Airline("haaah", 13, 8, "США", "https::/", 1));
		q.push(Airline("ahhah", 14, 1, "Япония", "https::/", 5));
		q.push(Airline("qyqyeuq", 15, 4, "Китай", "https::/", 7));
		q.push(Airline("ahasah", 16, 10, "США", "https::/", -5));
		q.push(Airline("ashashah ", 17, 7, "Россия", "https::/", -10));

		print_queue(q);
	}
	cout << "Задание 2.3\n";
	{
		Tree<Airline> t;

		t.Add(Airline("saf", 12, 1, "Россия", "https::/", 10));
		t.Add(Airline("haaah", 13, 8, "США", "https::/", 1));
		t.Add(Airline("ahhah", 14, 1, "Япония", "https::/", 5));
		t.Add(Airline("qyqyeuq", 15, 4, "Китай", "https::/", 7));
		t.Add(Airline("ahasah", 16, 10, "США", "https::/", -5));
		t.Add(Airline("ashashah ", 17, 7, "Россия", "https::/", -10));

		t.PreOrder(t.getRoot(), [](Node<Airline>* x)
			{
				cout << *x;
			});
	}
	cout << "\n\nЗадание 2.4\n\n";
	{
		Heap<Airline> Tree;
		Tree.Add(Airline("saf", 12, 1, "Россия", "https::/", 10));
		Tree.Add(Airline("haaah", 13, 8, "США", "https::/", 1));
		Tree.Add(Airline("ahhah", 14, 1, "Япония", "https::/", 5));
		Tree.Add(Airline("qyqyeuq", 15, 4, "Китай", "https::/", 7));
		Tree.Add(Airline("ahasah", 16, 10, "США", "https::/", -5));
		Tree.Add(Airline("ashashah ", 17, 7, "Россия", "https::/", -10));

		void(*f_ptr)(NodeHeap<Airline>*); f_ptr = print;
		Tree.InOrder(f_ptr);
	}
	cout << "\n\nЗадание 2.5\n\n";
	{
		Heap<Airline> Tree;
		Tree.Add(Airline("saf", 12, 1, "Россия", "https::/", 10));
		Tree.Add(Airline("haaah", 13, 8, "США", "https::/", 1));
		Tree.Add(Airline("ahhah", 14, 1, "Япония", "https::/", 5));
		Tree.Add(Airline("qyqyeuq", 15, 4, "Китай", "https::/", 7));
		Tree.Add(Airline("ahasah", 16, 10, "США", "https::/", -5));
		Tree.Add(Airline("ashashah ", 17, 7, "Россия", "https::/", -10));

		while (Tree.getCount())
		{
			Tree.ExtractMax().print();
			cout << '\n';
		}
	}
}