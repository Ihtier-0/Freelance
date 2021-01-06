#pragma once

#include <string>
#include <fstream>

#include "subscriber.h"

struct Node
{
	SUBSCRIBER info;
	Node* next;
	Node* prev;
};

typedef Node* TList;

class DoublyLinkedList
{
public:
	// заполнить список из файла
	DoublyLinkedList(const char* fileName);
	// создание первого элемента
	void First_node(const SUBSCRIBER& subscriber);
	// пустой список или нет
	bool Empty();
	// вставить после ноды
	void Add_after_node(TList pNode, const SUBSCRIBER& subscriber);
	// вставить до ноды
	void Add_before_node(TList pNode, const SUBSCRIBER& subscriber);
	// удалить ноду
	SUBSCRIBER& Delete(TList& pNode);
	// напечатать в фаил
	void PrintFile(const char* fileName);
	// очистить список
	~DoublyLinkedList();

	TList get_begin();
private:
	TList begin, end;
};