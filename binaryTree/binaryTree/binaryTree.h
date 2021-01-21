#pragma once

#include "treeNode.h"
#include <functional>

class binaryTree
{
public:
	typedef std::function<String(const String&)> Function;

	binaryTree();
	~binaryTree();

	void insert(String key);
	treeNode* search(String key);
	void remove(String key);
	void clear();

	void inorder(const Function& f);
	void postorder(const Function& f);
	void preorder(const Function& f);

private:
	void insert(String key, treeNode* leaf);
	treeNode* search(String key, treeNode* leaf);
	treeNode* remove(String key, treeNode* leaf);
	treeNode* findMin(treeNode* leaf);
	void inorder(const Function& f, treeNode* leaf);
	void postorder(const Function& f, treeNode* leaf);
	void preorder(const Function& f, treeNode* leaf);

	treeNode* m_root = nullptr;
};

