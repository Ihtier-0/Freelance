#pragma once

class treeNode
{
public:
	treeNode(int a_value, treeNode* a_left = nullptr, treeNode* a_right = nullptr);
	~treeNode();
	int value();
	void setValue(const int& a_value);
	treeNode* left();
	void set_left(treeNode* a_left);
	treeNode* right();
	void set_right(treeNode *a_right);
private:
	int m_value;
	treeNode *m_left, *m_right;
};

