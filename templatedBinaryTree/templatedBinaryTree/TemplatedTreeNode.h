#pragma once

template<class T>
class TemplatedTreeNode
{
public:
	TemplatedTreeNode(T a_value, TemplatedTreeNode* a_left = nullptr, TemplatedTreeNode* a_right = nullptr)
		: m_value(a_value), m_left(a_left), m_right(a_right) {}

	~TemplatedTreeNode()
	{
		if (m_left)
		{
			m_left->~TemplatedTreeNode<T>();
		}

		if (m_right)
		{
			m_right->~TemplatedTreeNode<T>();
		}

		m_value.~T();
	}
	int value()
	{
		return m_value;
	}
	void setValue(const T& a_value)
	{
		m_value = a_value;
	}
	TemplatedTreeNode<T>* left()
	{
		return m_left;
	}
	void set_left(TemplatedTreeNode<T>* a_left)
	{
		m_left = a_left;
	}
	TemplatedTreeNode<T>* right()
	{
		return m_right;
	}
	void set_right(TemplatedTreeNode<T>* a_right)
	{
		m_right = a_right;
	}
private:
	T m_value;
	TemplatedTreeNode<T>* m_left, * m_right;
};
