#pragma once

#include "treeNode.h"
#include <functional>

class binaryTree
{
public:
	typedef std::function<int(const int&)> Function;

	binaryTree();
	~binaryTree();

	void insert(int key);
	treeNode* search(int key);
	void remove(int key);
	void clear();

	void inorder(const Function& f);
	void postorder(const Function& f);
	void preorder(const Function& f);

private:
	void insert(int key, treeNode* leaf);
	treeNode* search(int key, treeNode* leaf);
	treeNode* remove(int key, treeNode* leaf);
	treeNode* findMin(treeNode* leaf);
	void inorder(const Function& f, treeNode* leaf);
	void postorder(const Function& f, treeNode* leaf);
	void preorder(const Function& f, treeNode* leaf);

	treeNode* m_root = nullptr;
};

