#pragma once

#include <iostream>
#include <string>

// базовый класс птицы
class bird
{
public:
	// конструктор который принимает идентификатор и состояние спит птица или нет
	bird(const std::string& identifier,
		const bool& sleep);
	// конструктор копирования
	bird(const bird& Bird);
	// оператор присваивания
	bird& operator=(const bird& Bird);
	// "спеть", чтобы хоть что-то добавить в производные классы
	virtual std::string sing() const = 0;
protected:
	// идентификатор (в виде произвольной строки символов)
	std::string m_identifier;
	// одно или несколько полей для хранения состояния (текущего значения) объекта
	bool m_sleep;
	// функции друга:
	// оператор вывода 
	friend std::ostream& operator<<(std::ostream& out, const bird& Bird);
	// оператор ввода
	friend std::istream& operator>>(std::istream& is, bird& Bird);
	// оператор сравнения
	friend bool operator==(const bird& bird1, const bird& bird2);
};

