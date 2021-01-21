#pragma once
#include <iostream>

class String
{
public:
	// Конструктор по умолчанию
	String();
	// Конструктор копирования
	String(const String& str);
	// Конструктор. bufSize - изначальный размер буфера
	String(int bufSize);
	// Конструктор, создающий объект на основании const char*
	String(const char* str);
	// Если передаваемая подстрока входит в строку, 
	// то возвращает индекс перевого вхождения. 
	// Иначе возвращает -1
	int indexOf(const char* str);
	// Добавляет к строке подстроку
	void add(const char* str);
	// Заменяет символ с заданным индексом новым символом.
	// Возвращает false, если символ с таким индексом отсутствует
	bool replace(int index, char c);
	// Вставляет подстроку по указанному индексу.
	// Возвращает false, если индекс отсутствует в текущей строке
	bool insert(int index, const char* str);
	// Выводит строку на экран
	void print() const;
	// Возвращает текущую длину строки
	int getLength();
	// Возвращает количество существующих 
	// на данный момент строк в программе
	static int getStringsNum();
	// Оператор присваивания
	String& operator=(const String& str);
	// Деструктор
	~String();
	// Оператор String + String
	friend String operator+(const String& str1, const String& str2);
	// Оператор const char* + String
	friend const char* operator+(const char* str1, const String& str2);
	// Оператор String + const char*
	friend String operator+(const String& str1, const char* str2);
	// Оператор String > String
	friend bool operator>(const String& str1, const String& str2);
	// Оператор String < String
	friend bool operator<(const String& str1, const String& str2);
	// Оператор String >= String
	friend bool operator>=(const String& str1, const String& str2);
	// Оператор String <= String
	friend bool operator<=(const String& str1, const String& str2);
	// Оператор String == String
	friend bool operator==(const String& str1, const String& str2);
	// Оператор String != String
	friend bool operator!=(const String& str1, const String& str2);

private:
	// Размер буфера по умолчанию
	static const int DEFAULT_BUF_SIZE = 32;
	// Массив, в котором хранится строка
	char* string;
	// Сколько символов в данный момент 
	// может содержать строка
	int bufSize;
	// Длина строки
	int length;
	// Количество строк на данный момент
	static int stringsNum;
	// Вставляет src в dst, начиная с index.
	// Предполагается, что в dst выделено достаточно места
	void insertTo(char* dst, int dstLen,
		const char* src, int srcLen, int index);
	// Считает, сколько места нужно выделить для создания 
	// строки указанной длины
	int countBufSize(int charsToAddCount);
};
