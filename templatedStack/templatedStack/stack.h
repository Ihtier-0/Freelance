#pragma once

#include "stackException.h"

template<class nodeDataType>
struct node
{
	node(nodeDataType data, node* next = nullptr) : m_data(data), m_next(next) {}
	nodeDataType m_data;
	node* m_next;
};

template<class stackDataType>
class Stack
{
public:
	~Stack();

	Stack() {};
	Stack(const Stack& stack);

	// добавить элемент в начало стека
	void push(const stackDataType& data);
	// забрать элемент из начала стека
	stackDataType pop();
	// прочитать элемент с начала стека
	stackDataType peek() const;

	unsigned int size() const;

	Stack& operator= (const Stack& drob);
private:
	node<stackDataType>* m_beginStack = nullptr;
	unsigned int m_size = 0;
};

template<class stackDataType>
inline Stack<stackDataType>::~Stack()
{
	if (m_beginStack)
	{
		node<stackDataType>* tmp;

		while (m_beginStack)
		{
			tmp = m_beginStack;
			m_beginStack = m_beginStack->m_next;
			tmp->m_data.~stackDataType();
			delete tmp;
		}
	}

	m_size = 0;
}

template<class stackDataType>
inline Stack<stackDataType>::Stack(const Stack& stack)
{
	m_size = stack.m_size;

	node<stackDataType>* cur = stack.m_beginStack;
	node<stackDataType>* end = nullptr;

	while (cur)
	{
		node<stackDataType>* n = new node<stackDataType>(cur->m_data);

		if (!m_beginStack)
		{
			m_beginStack = n;
			end = n;
		}
		else
		{
			end->m_next = n;
			end = n;
		}

		cur = cur->m_next;
	}
}

template<class stackDataType>
inline void Stack<stackDataType>::push(const stackDataType& data)
{
	m_beginStack = new node<stackDataType>(data, m_beginStack);
	++m_size;
}

template<class stackDataType>
inline stackDataType Stack<stackDataType>::pop()
{
	if (m_beginStack)
	{
		node<stackDataType>* tmp = m_beginStack;
		stackDataType popData = tmp->m_data;
		m_beginStack = m_beginStack->m_next;

		delete tmp;

		--m_size;
		return popData;
	}
	else
	{
		throw stackException("begin stack - nullptr");
	}
}

template<class stackDataType>
inline stackDataType Stack<stackDataType>::peek() const
{
	if (m_beginStack)
	{
		return m_beginStack->m_data;
	}
	else
	{
		throw stackException("begin stack - nullptr");
	}
}

template<class stackDataType>
inline unsigned int Stack<stackDataType>::size() const
{
	return m_size;
}


template<class stackDataType>
inline Stack<stackDataType>& Stack<stackDataType>::operator=(const Stack<stackDataType>& stack)
{
	m_size = stack.m_size;

	node<stackDataType>* cur = stack.m_beginStack;
	node<stackDataType>* end = nullptr;

	while (cur)
	{
		node<stackDataType>* n = new node<stackDataType>(cur->m_data);

		if (!m_beginStack)
		{
			m_beginStack = n;
			end = n;
		}
		else
		{
			end->m_next = n;
			end = n;
		}

		cur = cur->m_next;
	}

	return *this;
}