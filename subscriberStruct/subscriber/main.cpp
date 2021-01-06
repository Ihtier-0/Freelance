/*
I. «Абонент сотовой телефонной сети»
Структура записи:
 ФИО
 Адрес:
 улица
 номер дома
 квартира
 Номер телефона
 Баланс
Записи упорядочены по ФИО. Напечатайте информацию об абонентах, имеющих два и более телефонных номера.
Сделать 2 лабораторных по этому заданию. Одну в виде двунаправленных списков, вторую в виде классов
С++

!!!стиль написания кода требование заказчика!!!
*/

#include <windows.h>
#include <iostream>

#include "DoublyLinkedList.h"

bool task_1(DoublyLinkedList &Dlist)
{
	bool result = false;
	TList tmp = Dlist.begin;

	while (tmp->next)
	{
		if (tmp->info.fullName == tmp->next->info.fullName)
		{
			std::cout << tmp->info.fullName << '\n';
			
			std::string tmpStr = tmp->info.fullName;

			while (tmp->info.fullName == tmpStr)
			{
				tmp = tmp->next;
			}

			result = true;
		}

		tmp = tmp->next;
	}

	return result;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	DoublyLinkedList DList;

	std::ifstream file("input.txt");

	if (!file)
	{
		std::cout << "Фаил не найден!\n";
	}
	else
	{
		DList.CreateList("input.txt");
		DList.PrintFile("result.txt");

		std::cout << "Информация об абонентах имеющих 2 или более телефонных номера:\n";
		if (!task_1(DList))
		{
			std::cout << "Таких абонентов нет!\n";
		}

		DList.Clear();
	}

	std::cout << "*****\n";

	return 0;
}