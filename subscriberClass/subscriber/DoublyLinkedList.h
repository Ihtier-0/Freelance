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
	// ��������� ������ �� �����
	DoublyLinkedList(const char* fileName);
	// �������� ������� ��������
	void First_node(const SUBSCRIBER& subscriber);
	// ������ ������ ��� ���
	bool Empty();
	// �������� ����� ����
	void Add_after_node(TList pNode, const SUBSCRIBER& subscriber);
	// �������� �� ����
	void Add_before_node(TList pNode, const SUBSCRIBER& subscriber);
	// ������� ����
	SUBSCRIBER& Delete(TList& pNode);
	// ���������� � ����
	void PrintFile(const char* fileName);
	// �������� ������
	~DoublyLinkedList();

	TList get_begin();
private:
	TList begin, end;
};