#include "treeNode.h"

treeNode::treeNode(const String& a_value, treeNode* a_left, treeNode* a_right)
	: m_value(a_value), m_left(a_left), m_right(a_right) {}

treeNode::~treeNode()
{
	if (m_left)
	{
		m_left->~treeNode();
	}

	if (m_right)
	{
		m_right->~treeNode();
	}
}

String treeNode::value()
{
	return m_value;
}

void treeNode::setValue(const String& a_value)
{
	m_value = a_value;
}

treeNode* treeNode::left()
{
	return m_left;
}

void treeNode::set_left(treeNode* a_left)
{
	m_left = a_left;
}

treeNode* treeNode::right()
{
	return m_right;
}

void treeNode::set_right(treeNode* a_right)
{
	m_right = a_right;
}
