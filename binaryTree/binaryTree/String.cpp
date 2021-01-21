#include "String.h"

// Количество строк на данный момент
int String::stringsNum = 0;

// Конструктор по умолчанию
String::String()
{
	stringsNum++;
	bufSize = DEFAULT_BUF_SIZE;
	length = 0;
	string = new char[bufSize];
	for (int i = 0; i < bufSize; i++)
	{
		string[i] = '\0';
	}
}

// Конструктор копирования
String::String(const String& str)
{
	stringsNum++;
	bufSize = str.bufSize;
	length = str.length;
	string = new char[bufSize];
	for (int i = 0; i < bufSize; i++)
	{
		string[i] = str.string[i];
	}
}

// Вставляет src в dst, начиная с index.
// Предполагается, что в dst выделено достаточно места
void String::insertTo(char* dst, int dstLen,
	const char* src, int srcLen, int index)
{
	for (int i = dstLen + srcLen - 1; i > index + srcLen - 1; i--)
		dst[i] = dst[i - srcLen];
	for (int i = index, j = 0; j < srcLen; i++, j++)
		dst[i] = src[j];
}

// Конструктор. bufSize - изначальный размер буфера
String::String(int bufSize)
{
	stringsNum++;
	this->bufSize = bufSize;
	length = 0;
	string = new char[bufSize];
	for (int i = 0; i < bufSize; i++)
		string[i] = '\0';
}

// Конструктор, создающий объект на основании const char*
String::String(const char* str)
{
	stringsNum++;
	bufSize = 0;
	length = 0;
	int charsNum = 0;
	for (int i = 0; str[i] != '\0'; i++)
		charsNum++;
	bufSize = countBufSize(charsNum);
	length = charsNum;
	string = new char[bufSize];
	for (int i = 0; i < charsNum; i++)
		string[i] = str[i];
	for (int i = charsNum; i < bufSize; i++)
	{
		string[i] = '\0';
	}

}

// Если передаваемая подстрока входит в строку, 
// то возвращает индекс перевого вхождения. 
// Иначе возвращает -1
int String::indexOf(const char* str)
{
	int index = -1;
	int j = -1;
	bool found = false;
	for (int i = 0; i < length && !found; i++)
	{
		if (index == -1)
		{
			if (string[i] == str[0])
			{
				index = i;
				j = 1;
			}
		}
		else
		{
			if (str[j] == '\0')
				found = true;
			else if (str[j] == string[i])
				j++;
			else
				index = -1;
		}
	}

	return index;
}

// Считает, сколько места нужно выделить для создания 
// строки указанной длины
int String::countBufSize(int charsToAddCount)
{
	int delta = charsToAddCount - bufSize + length;
	int addToBuf = ((int)(delta / DEFAULT_BUF_SIZE) + 1) * DEFAULT_BUF_SIZE;
	int newBufSize = bufSize + addToBuf;
	return newBufSize;
}

// Добавляет к строке подстроку
void String::add(const char* str)
{
	// Находим индекс, с которого начинаем добавление
	int startIndex = bufSize - 1;
	while (string[startIndex] != '\0')
		startIndex--;
	// Узнаём, сколько символов нужно добавить
	int charsToAddCount = 0;
	for (int i = 0; str[i] != '\0'; i++)
		charsToAddCount++;
	if ((length + charsToAddCount) >= bufSize)
	{
		// Считаем, сколько нужно места для новой строки и выделяем память
		int newBufSize = countBufSize(charsToAddCount);
		// Выделяем место под новую строку
		char* newString = new char[newBufSize];
		// Копируем старую строку в новый массив
		for (int i = 0; i < length; i++)
			newString[i] = string[i];
		// Добавляем новую строку
		for (int i = length, j = 0; j < charsToAddCount; i++, j++)
			newString[i] = str[j];
		// Заполняем остаток строки '\0'
		for (int i = length + charsToAddCount; i < newBufSize; i++)
			newString[i] = '\0';
		// Обновляем значения полей данных
		delete string;
		string = newString;
		length += charsToAddCount;
		bufSize = newBufSize;
	}
	else
	{
		// Копируем подстроку в нашу строку
		for (int i = length, j = 0; str[j] != '\0'; i++, j++)
			string[i] = str[j];
		length += charsToAddCount;
	}
}

// Заменяет символ с заданным индексом новым символом.
// Возвращает false, если символ таким индексом отсутствует
bool String::replace(int index, char c)
{
	if (index < bufSize)
	{
		if (string[index] == '\0')
			return false;
		else
		{
			string[index] = c;
			return true;
		}
	}
	else
		return false;
}

// Вставляет подстроку по указанному индексу.
// Возвращает false, если индекс отсутствует в текущей строке
bool String::insert(int index, const char* str)
{
	if (index > length)
		return false;
	// Узнаём, сколько символов нужно добавить
	int charsToAddCount = 0;
	for (int i = 0; str[i] != '\0'; i++)
		charsToAddCount++;

	if ((length + charsToAddCount) >= bufSize)
	{
		// Считаем, сколько нужно места для новой строки и выделяем память
		int newBufSize = countBufSize(charsToAddCount);
		// Выделяем место под новую строку
		char* newString = new char[newBufSize];
		// Копируем старую строку в новый массив
		for (int i = 0; i < length; i++)
			newString[i] = string[i];
		// Вставляем новую строку
		insertTo(newString, length, str, charsToAddCount, index);
		// Заполняем остаток строки '\0'
		for (int i = length + charsToAddCount; i < newBufSize; i++)
			newString[i] = '\0';
		// Обновляем значения полей данных
		delete string;
		string = newString;
		bufSize = newBufSize;
	}
	else
		// Вставляем подстроку в нашу строку
		insertTo(string, length, str, charsToAddCount, index);
	length += charsToAddCount;
	return true;
}

// Выводит строку на экран
void String::print() const
{
	std::cout << string;
}

// Возвращает текущую длину строки
int String::getLength()
{
	return length;
}

// Возвращает количество существующих 
// на данный момент строк в программе
int String::getStringsNum()
{
	return stringsNum;
}

// Оператор присваивания
String& String::operator=(const String& str)
{
	if (str == *this)
		return *this;
	this->bufSize = str.bufSize;
	this->length = str.length;
	if (this->string != nullptr)
		delete this->string;
	this->string = new char[bufSize];
	for (int i = 0; i < bufSize; i++)
	{
		this->string[i] = str.string[i];
	}
	return *this;
}

// Деструктор
String::~String()
{
	if (string)
	{
		delete string;
	}
	stringsNum--;
}

// Оператор String + String
String operator+(const String& str1, const String& str2)
{
	String str(str1);
	str.add(str2.string);
	return str;
}

// Оператор const char* + String
const char* operator+(const char* str1, const String& str2)
{
	int str1Length = 0;
	for (int i = 0; str1[i] != '\0'; i++)
		str1Length++;
	char* str = new char[str1Length + str2.length + 1];
	for (int i = 0; i < str1Length; i++)
		str[i] = str1[i];
	for (int i = str1Length, j = 0; j < str2.length; i++, j++)
		str[i] = str2.string[j];
	str[str1Length + str2.length] = '\0';
	const char* str3 = str;
	return str3;
}

// Оператор String + const char*
String operator+(const String& str1, const char* str2)
{
	String str(str1);
	str.add(str2);
	return str;
}

// Оператор String > String
bool operator>(const String& str1, const String& str2)
{
	if (str1.length > str2.length)
		return true;
	else if (str1.length < str2.length)
		return false;
	else
	{
		for (int i = 0; i < str1.length; i++)
		{
			if (str1.string[i] > str2.string[i])
				return true;
			else if (str1.string[i] < str2.string[i])
				return false;
		}
	}
	return false;
}

// Оператор String < String
bool operator<(const String& str1, const String& str2)
{
	if (str1.length < str2.length)
		return true;
	else if (str1.length > str2.length)
		return false;
	else
	{
		for (int i = 0; i < str1.length; i++)
		{
			if (str1.string[i] < str2.string[i])
				return true;
			else if (str1.string[i] > str2.string[i])
				return false;
		}
	}
	return false;
}

// Оператор String >= String
bool operator>=(const String& str1, const String& str2)
{
	if (str1.length > str2.length)
		return true;
	else if (str1.length < str2.length)
		return false;
	else
	{
		for (int i = 0; i < str1.length; i++)
		{
			if (str1.string[i] < str2.string[i])
				return false;
			else if (str1.string[i] > str2.string[i])
				return true;
		}
	}
	return true;
}

// Оператор String <= String
bool operator<=(const String& str1, const String& str2)
{
	if (str1.length < str2.length)
		return true;
	else if (str1.length > str2.length)
		return false;
	else
	{
		for (int i = 0; i < str1.length; i++)
		{
			if (str1.string[i] > str2.string[i])
				return false;
			else if (str1.string[i] < str2.string[i])
				return true;
		}
	}
	return true;
}

// Оператор String == String
bool operator==(const String& str1, const String& str2)
{
	if (str1.length != str2.length)
		return false;
	else
	{
		for (int i = 0; i < str1.length; i++)
		{
			if (str1.string[i] != str2.string[i])
				return false;
		}
	}
	return true;
}

// Оператор String != String
bool operator!=(const String& str1, const String& str2)
{
	if (str1.length != str2.length)
		return true;
	else
	{
		for (int i = 0; i < str1.length; i++)
		{
			if (str1.string[i] != str2.string[i])
				return true;
		}
	}
	return false;
}
