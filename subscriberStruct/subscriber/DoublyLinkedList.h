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
	// �������� ������� ��������
	void First_node(const Subscriber& subscriber);
	// ������ ������ ��� ���
	bool Empty();
	// �������� ����� ����
	void Add_after_node(TList pNode, const Subscriber& subscriber);
	// �������� �� ����
	void Add_before_node(TList pNode, const Subscriber& subscriber);
	// ������� ����
	Subscriber& Delete(TList& pNode);
	// ��������� ������ �� �����
	void CreateList(const char* fileName);
	// ���������� � ����
	void PrintFile(const char* fileName);
	// �������� ������
	void Clear();

	TList begin, end;
};