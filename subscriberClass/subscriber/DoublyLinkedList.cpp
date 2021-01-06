#include "DoublyLinkedList.h"

void DoublyLinkedList::First_node(const SUBSCRIBER& subscriber)
{
	begin = new Node;
	begin->info = subscriber;
	begin->next = nullptr;
	begin->prev = nullptr;
	end = begin;
}

bool DoublyLinkedList::Empty()
{
	return begin == nullptr;
}

void DoublyLinkedList::Add_after_node(TList pNode, const SUBSCRIBER& subscriber)
{
	TList tmp = new Node;
	tmp->info = subscriber;
	tmp->next = pNode->next;
	tmp->prev = pNode;

	if (pNode == end)
	{
		end = tmp;
	}
	else
	{
		pNode->next->next = tmp;
	}

	pNode->next = tmp;
}

void DoublyLinkedList::Add_before_node(TList pNode, const SUBSCRIBER& subscriber)
{
	TList tmp = new Node;
	tmp->info = subscriber;
	tmp->next = pNode;
	tmp->prev = pNode->prev;

	if (pNode == begin)
	{
		begin = tmp;
	}
	else
	{
		pNode->prev->next = tmp;
	}

	pNode->prev = tmp;
}

SUBSCRIBER& DoublyLinkedList::Delete(TList& pNode)
{
	TList tmp = pNode;
	if (pNode == begin)// в голове списка
	{
		begin = tmp->next;
		if (begin)
		{
			begin->prev = nullptr;
		}
	}
	else
	{
		if (pNode == end)//в хвосте списка
		{
			end = tmp->prev;
			end->next = nullptr;
		}
		else //в середине списка
		{
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;

		}
	}//элемент исключен из списка

	SUBSCRIBER student = tmp->info;

	return student;
}

//ищем строго больший элемент
TList Found_place(const TList begin, const SUBSCRIBER& subscriber)
{
	TList tmp = begin;

	while (tmp && tmp->info.compare_fullName(subscriber) <= 0)
	{
		tmp = tmp->next;
	}

	return tmp;
}

DoublyLinkedList::DoublyLinkedList(const char* fileName)
{
	std::ifstream file(fileName);

	SUBSCRIBER subscriber(file);
	this->First_node(subscriber);

	TList place;

	while (!file.eof())
	{
		file.get();
		SUBSCRIBER subscriber(file);
		place = Found_place(begin, subscriber);

		if (place)
		{
			Add_before_node(place, subscriber);
		}
		else
		{
			Add_after_node(end, subscriber);
		}
	}

	file.close();
}

void DoublyLinkedList::PrintFile(const char* fileName)
{
	std::ofstream file(fileName);

	TList tmp = begin;

	while (tmp)
	{
		tmp->info.print_to_file(file);
		tmp = tmp->next;
	}

	file.close();
}

DoublyLinkedList::~DoublyLinkedList()
{
	while (!this->Empty())
	{
		this->Delete(begin);
	}
}

TList DoublyLinkedList::get_begin()
{
	return begin;
}
