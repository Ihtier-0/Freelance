#pragma once

#include <string>
#include <fstream>

#include "subscriber.h"

struct Node
{
	Subscriber info;
	Node* next;
	Node* prev;
};

typedef Node* TList;

struct DoublyLinkedList
{
	// создание первого элемента
	void First_node(const Subscriber& subscriber);
	// пустой список или нет
	bool Empty();
	// вставить после ноды
	void Add_after_node(TList pNode, const Subscriber& subscriber);
	// вставить до ноды
	void Add_before_node(TList pNode, const Subscriber& subscriber);
	// удалить ноду
	Subscriber& Delete(TList& pNode);
	// заполнить список из файла
	void CreateList(const char* fileName);
	// напечатать в фаил
	void PrintFile(const char* fileName);
	// очистить список
	void Clear();

	TList begin, end;
};