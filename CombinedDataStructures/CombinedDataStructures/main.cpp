#include <iostream>
#include <algorithm>
#include <set>
#include <ctime>
#include <iterator>
#include <chrono>
#include <vector>

using namespace std;

using MySet = std::set<int>;
using MyIt = std::set<int>::iterator;
using MySeq = std::vector<MyIt>;

const int lim = 100; //ОГРАНИЧИТЕЛЬ для множества ключей

class MyCont
{
	int power;
	char tag;
	MySet A;
	MySeq sA;
	MyCont& operator = (const MyCont&) = delete;
	MyCont& operator = (MyCont&&) = delete;
public:
	void setTag(const char& newTag)
	{
		tag = newTag;
	}

	MyCont(int, char);
	MyCont(const MyCont&);
	MyCont(MyCont&&) noexcept;
	MyCont& operator |= (const MyCont&);
	MyCont operator | (const MyCont& rgt) const
	{
		MyCont result(*this); return (result |= rgt);
	}
	MyCont& operator &= (const MyCont&);
	MyCont operator & (const MyCont& rgt) const
	{
		MyCont result(*this); return (result &= rgt);
	}
	MyCont& operator -= (const MyCont&);
	MyCont operator - (const MyCont& rgt) const
	{
		MyCont result(*this); return (result -= rgt);
	}
	// надо
	void Merge(const MyCont&);
	void Erase(size_t, size_t);
	void Change(const MyCont&, size_t);

	void Concat(const MyCont&);

	void Subst(const MyCont&, size_t);
	void Show() const;
	size_t Power() const { return sA.size(); }
	friend void PrepareAnd(MyCont&, MyCont&, const int);	
	friend MyCont XOR(const MyCont& m1, const MyCont& m2)
	{
		return ((m1 | m2) - (m1 & m2));
	}
};

MyCont::MyCont(int p = 0, char t = 'R') : power(p), tag(t)
{
	for (int i = 0; i < power; ++i)
	{
		sA.push_back(A.insert(std::rand() % lim).first);
	}
}

MyCont::MyCont(MyCont&& source) noexcept //Копия "с переносом"
	: power(source.power), tag(source.tag),
	A(std::move(source.A)), sA(std::move(source.sA)) { }

MyCont::MyCont(const MyCont& source) //Конструктор копии
	: power(source.power), tag(source.tag)
{
	for (auto x : source.A) sA.push_back(A.insert(x).first);
}

void MyCont::Show() const
{
	using std::cout;
	cout << "\n" << tag << ": ";

	for (auto x : A)
	{
		cout << x << " "; //Выдача множества
	}
	cout << "\n < ";

	for (auto x : sA)
	{
		cout << *x << " "; //Выдача последовательности
	}
	cout << ">";
}

void PrepareAnd(MyCont& first, MyCont& second, const int quantity)
{
	for (int i = 0; i < quantity; ++i)
	{ //Подготовка пересечения:
		int x = rand() % lim;		// добавление общих эл-тов
		first.sA.push_back(first.A.insert(x).first);
		second.sA.push_back(second.A.insert(x).first);
	}
}

MyCont& MyCont::operator -= (const MyCont& rgt)
{ //Разность мн-в
	MySet temp;
	MySeq stemp;
	for (auto x : A)
	{
		if (rgt.A.find(x) == rgt.A.end())
		{
			stemp.push_back(temp.insert(x).first);
		}
	}
	temp.swap(A);
	stemp.swap(sA);
	return *this;
}

MyCont& MyCont::operator &= (const MyCont& rgt) { //Пересечение
	MySet temp;
	MySeq stemp;
	for (auto x : A)
	{
		if (rgt.A.find(x) != rgt.A.end())
		{
			stemp.push_back(temp.insert(x).first);
		}
	}
	temp.swap(A);
	stemp.swap(sA);
	return *this;
}

MyCont& MyCont::operator |= (const MyCont& rgt)
{ //Объединение
	for (auto x : rgt.A)
	{
		sA.push_back(A.insert(x).first);
	}
	return *this;
}

void MyCont::Erase(size_t p, size_t q)
{ //Исключение фр-та от p до q
	using std::min;
	size_t r(Power());
	p = min(p, r);
	q = min(q + 1, r);

	if (p <= q)
	{
		MySet temp;
		MySeq stemp;
		for (size_t i = 0; i < p; ++i)
		{
			stemp.push_back(temp.insert(*sA[i]).first);
		}
		for (size_t i = q; i < r; ++i)
		{
			stemp.push_back(temp.insert(*sA[i]).first);
		}
		A.swap(temp);
		sA.swap(stemp);
	}
}
void MyCont::Merge(const MyCont& rgt)
{ //Слияние
	using std::sort;
	MySeq temp(rgt.sA), res;
	auto le = [](MyIt a, MyIt b)->bool
	{ return *a < *b; };//Критерий

	sort(sA.begin(), sA.end(), le);

	sort(temp.begin(), temp.end(), le);

	std::merge(sA.begin(), sA.end(), temp.begin(), temp.end(),
		std::back_inserter(res), le); //Слияние для последовательностей...

	A.insert(rgt.A.begin(), rgt.A.end()); //... и объединение множеств

	sA.swap(res);
}
void MyCont::Change(const MyCont& rgt, size_t p)
{ //Замена
	if (p >= Power())
	{
		Concat(rgt);
	}
	else
	{
		MySeq stemp(sA.begin(), sA.begin() + p);	//Начало
		std::copy(rgt.sA.begin(), rgt.sA.end(), back_inserter(stemp));
		//Замена
		size_t q = p + rgt.Power();
		if (q < Power())
		{
			std::copy(sA.begin() + q, sA.end(), back_inserter(stemp));
		}
		//Окончание
		MySet temp;
		sA.clear();
		for (auto x : stemp)
		{
			sA.push_back(temp.insert(*x).first);
		}
		A.swap(temp);
	}
}

void MyCont::Concat(const MyCont& rgt)
{ //Сцепление
	for (auto x : rgt.sA)
	{
		sA.push_back(A.insert(*x).first);
	}
}

void MyCont::Subst(const MyCont& rgt, size_t p)
{ //Подстановка
	if (p >= Power())
	{
		Concat(rgt);
	}
	else
	{
		MySeq stemp(sA.begin(), sA.begin() + p);	//Начало
		std::copy(rgt.sA.begin(), rgt.sA.end(), back_inserter(stemp)); //Вставка
		std::copy(sA.begin() + p, sA.end(), back_inserter(stemp)); //Окончание
		MySet temp;
		sA.clear();

		for (auto x : stemp)
		{
			sA.push_back(temp.insert(*x).first);
		}
		A.swap(temp);
	}
}

int main()
{
	using std::cout;
	using namespace std::chrono;
	setlocale(LC_ALL, "Russian");
	srand((unsigned int)time(nullptr));

	bool debug = true; //false, чтобы запретить отладочный вывод
	auto MaxMul = 5;
	int middle_power = 0, set_count = 0;

	auto Used = [&](MyCont& t)
	{
		middle_power += t.Power();
		++set_count;
	};

	auto DebOut = [debug](MyCont& t) 
	{
		if (debug)
		{
			t.Show();
			cout << " Press <Enter>";
			cin.get();
		}
	};

	auto rand = [](int d)
	{
		return std::rand() % d;
	}; 
	int p = 10;
	//=== Данные ===
	MyCont A(p, 'A');
	MyCont B(p, 'B');
	MyCont C(p, 'C');
	MyCont D(p, 'D');
	MyCont E(p, 'E');

	A.Show();
	B.Show();
	C.Show();
	D.Show();
	E.Show();

	MyCont F(A & B);
	F.setTag('F');
	std::cout << "\nA & B";
	F.Show();

	MyCont G(XOR(F, C));
	G.setTag('G');
	std::cout << "\nA & B xor C";
	G.Show();

	MyCont H(G & D);
	H.setTag('H');
	std::cout << "\nA & B xor C & D";
	H.Show();

	MyCont K(H & E);
	K.setTag('K');
	std::cout << "\nA & B xor C & D & E";
	K.Show();

	MyCont M(A);
	M.setTag('M');
	A.Show();
	B.Show();
	cout << "\nMERGE";
	M.Merge(B);
	M.Show();

	MyCont R(A);
	R.setTag('R');
	R.Show();
	cout << "\nERASE";
	R.Erase(1, 3);
	R.Show();

	MyCont T(A);
	T.setTag('T');
	A.Show();
	B.Show();
	cout << "\nCHANGE";
	T.Change(B, 5);
	T.Show();

	cin.get();
	return 0;
}
