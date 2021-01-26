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
		cout << "�������� �����: " << it_m->first << ", �����: " << it_m->second << "\n";
		it_m++;
	}
}

//����
template<class T>
class Node
{
protected:
	//�������� ���������� Node N; N.data = 10 ������� ������
	T data;
	//�� ����� ������� Node, �� ����� ����� ������� ���������
	Node* left;
	Node* right;
	Node* parent;
	//����������, ����������� ��� ����������� ������� ������
	int height;
public:
	//��������� ����� ���������� � �������
	virtual void setData(T d) { data = d; }
	virtual T getData() { return data; }
	int getHeight() { return height; }
	virtual Node* getLeft() { return left; }
	virtual Node* getRight() { return right; }
	virtual Node* getParent() { return parent; }
	virtual void setLeft(Node* N) { left = N; }
	virtual void setRight(Node* N) { right = N; }
	virtual void setParent(Node* N) { parent = N; }
	//�����������. ������������� ��������� �������� ��� ����������
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
	//������ - ��� ���������� ��� �������� ����� ������
	Node<T>* root;
public:
	//������ � ��������� ��������
	virtual Node<T>* getRoot() { return root; }
	//����������� ������: � ������ �������� ������ �� ������ ���� ���, ������ ������� � ������
	Tree<T>() { root = NULL; }
	//������������ ������� ���������� ����. �������� ����������, �� �������� ���� ���� - ���������� � ����� ��� ������ ���������
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
			//���� �����
			if (Current->getLeft() != NULL)
				Current->setLeft(Add_R(N, Current->getLeft()));
			else
				Current->setLeft(N);
			Current->getLeft()->setParent(Current);
		}
		if (Current->getData() < N->getData())
		{
			//���� ������
			if (Current->getRight() != NULL)
				Current->setRight(Add_R(N, Current->getRight()));
			else
				Current->setRight(N);
			Current->getRight()->setParent(Current);
		}
		if (Current->getData() == N->getData())
			//����� ����������
			;
		//��� ������������������� ������ ������
		return Current;
	}
	//������� ��� ���������� �����. ������ ����� ���� � ����� ������� � �������� ������ ������� ���������� � ������
	virtual void Add(T n)
	{
		Node<T>* N = new Node<T>;
		N->setData(n);
		Add_R(N);
	}
	virtual Node<T>* Min(Node<T>* Current = NULL)
	{
		//������� - ��� ����� "�����" ����. ��� �� ������ ������ �����
		if (root == NULL) return NULL;
		if (Current == NULL)
			Current = root;
		while (Current->getLeft() != NULL)
			Current = Current->getLeft();
		return Current;
	}
	virtual Node<T>* Max(Node<T>* Current = NULL)
	{
		//������� - ��� ����� "������" ����. ��� �� ������ ������ ������
		if (root == NULL) return NULL;
		if (Current == NULL)
			Current = root;
		while (Current->getRight() != NULL)
			Current = Current->getRight();
		return Current;
	}
	//����� ���� � ������. ������ �������� - � ����� ��������� ������, ������ - ��� ������
	virtual Node<T>* Find(T data, Node<T>* Current)
	{
		//���� ��������
		if (Current == NULL) return NULL;
		if (Current->getData() == data) return Current;
		//����������� �����
		if (Current->getData() > data) return Find(data, Current->getLeft());
		if (Current->getData() < data) return Find(data, Current->getRight());
	}
	//��� ������ ������
	virtual void PreOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL)
			f(N);
		if (N != NULL && N->getLeft() != NULL)
			PreOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PreOrder(N->getRight(), f);
	}
	//InOrder-����� ���� ��������������� ������������������
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
	//���������� ������ � ����
	T getValue() { return value; }
	void setValue(T v) { value = v; }
	//��������� �����
	int operator<(NodeHeap N)
	{
		return (value < N.getValue());
	}
	int operator>(NodeHeap N)
	{
		return (value > N.getValue());
	}
	//����� ����������� ������ ����
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

//���� (heap)
template <class T>
class Heap
{
private:
	//������
	NodeHeap<T>* arr;
	//������� ��������� ���������
	int len;
	//������� ������ ��������
	int size;
public:
	// TODO
	NodeHeap<T>* ExtractMax()
	{

	}
	//������ � ��������������� ����� ���� � �������� �������
	int getCapacity() { return size; }
	int getCount() { return len; }
	NodeHeap<T>& operator[](int index)
	{
		if (index < 0 || index >= len)
			;//?
		return arr[index];
	}
	//�����������
	Heap<T>(int MemorySize = 100)
	{
		arr = new NodeHeap<T>[MemorySize];
		len = 0;
		size = MemorySize;
	}
	//�������� ������� �������� arr[index1], arr[index2]
	void Swap(int index1, int index2)
	{
		if (index1 <= 0 || index1 >= len)
			;
		if (index2 <= 0 || index2 >= len)
			;
		//����� ����� ������ �� ������
		NodeHeap<T> temp;
		temp = arr[index1];
		arr[index1] = arr[index2];
		arr[index2] = temp;
	}
	//����������� ������ ����� ����� ������
	void Copy(NodeHeap<T>* dest, NodeHeap<T>* source)
	{
		dest->setValue(source->getValue());
	}
	//������� ��������� ������, ������� ��������� ��������, �������� ��� �� �������� � �������
	NodeHeap<T>* GetLeftChild(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//����� ����� ������ �� ������
		return &arr[index * 2 + 1];
	}
	NodeHeap<T>* GetRightChild(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//����� ����� ������ �� ������
		return &arr[index * 2 + 2];
	}
	NodeHeap<T>* GetParent(int index)
	{
		if (index <= 0 || index >= len)
			;
		//����� ����� ������ �� ������
		if (index % 2 == 0)
			return &arr[index / 2 - 1];
		return &arr[index / 2];
	}
	int GetLeftChildIndex(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//����� ����� ������ �� ������
		return index * 2 + 1;
	}
	int GetRightChildIndex(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//����� ����� ������ �� ������
		return index * 2 + 2;
	}
	int GetParentIndex(int index)
	{
		if (index <= 0 || index >= len)
			;
		//����� ����� ������ �� ������
		if (index % 2 == 0)
			return index / 2 - 1;
		return index / 2;
	}
	//�������� ������� �����
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
			//����� ����������� �����
			Swap(parent, max_index);
			SiftUp(parent);
		}
	}
	//���������� �������� - ��������� ��� � ����� ������� � ���������� �����
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
	//����������� �������� ���� � ��������� � ��� �������
	void Straight(void(*f)(NodeHeap<T>*))
	{
		int i;
		for (i = 0; i < len; i++)
		{
			f(&arr[i]);
		}
	}
	//������� ���������, ����������� �������� ��������� ������
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

	cout << "������� 2.1\n";

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

	if (find_key<string, unsigned int>(m, name, circulation))
	{
		cout << "����� ���� �����: " << circulation << '\n';
	}
	else
	{
		cout << "����� ����� ���!\n";
	}

	cout << "������� ����� �����: ";
	cin >> circulation;

	if (find_value<string, unsigned int>(m, circulation, name))
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

	cout << "������� 2.2\n";

	cout << "������� 2.3\n";

	Tree<book> t;
	
	t.Add(book("������", "����", "������", 1500, "��������", 10, book::typeOfPublication::audio, 10000));
	t.Add(book("������", "������", "�����", 150, "��������", 10, book::typeOfPublication::electronic, 10000));
	t.Add(book("������", "������", "����", 1, "��������", 10, book::typeOfPublication::paper, 10000));
	t.Add(book("������", "���������", "���������", 100, "��������", 10, book::typeOfPublication::electronic, 10000));
	t.Add(book("������", "����", "�����", 15000, "��������", 10, book::typeOfPublication::audio, 10000));
	t.Add(book("������", "���", "��������", 1500, "��������", 10, book::typeOfPublication::paper, 10000));

	t.PreOrder(t.getRoot(), [](Node<book>*x)
		{
			cout << *x;
		});

	cout << "\n������� 2.4\n";

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