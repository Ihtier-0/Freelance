#pragma once

#include "String.h"

class treeNode
{
public:
	treeNode(const String& a_value, treeNode* a_left = nullptr, treeNode* a_right = nullptr);
	~treeNode();
	String value();
	void setValue(const String& a_value);
	treeNode* left();
	void set_left(treeNode* a_left);
	treeNode* right();
	void set_right(treeNode *a_right);
private:
	String m_value;
	treeNode *m_left, *m_right;
};

