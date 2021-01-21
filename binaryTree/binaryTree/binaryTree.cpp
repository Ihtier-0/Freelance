#include "binaryTree.h"

binaryTree::binaryTree() : m_root(nullptr) {}

binaryTree::~binaryTree()
{
	if (m_root)
	{
		m_root->~treeNode();
	}
	m_root = nullptr;
}

void binaryTree::insert(String key)
{
	if (m_root)
	{
		insert(key, m_root);
	}
	else
	{
		m_root = new treeNode(key);
	}
}

treeNode* binaryTree::search(String key)
{
	return search(key, m_root);
}

void binaryTree::remove(String key)
{
	remove(key, m_root);
}

void binaryTree::clear()
{
	this->~binaryTree();
	delete m_root;
	m_root = nullptr;
}

void binaryTree::inorder(const Function& f)
{
	inorder(f, m_root);
}

void binaryTree::postorder(const Function& f)
{
	postorder(f, m_root);
}

void binaryTree::preorder(const Function& f)
{
	preorder(f, m_root);
}

void binaryTree::insert(String key, treeNode* leaf)
{
	if (key < leaf->value())
	{
		if (leaf->left())
		{
			insert(key, leaf->left());
		}
		else
		{
			leaf->set_left(new treeNode(key));
		}
	}
	else if (key >= leaf->value())
	{
		if (leaf->right())
		{
			insert(key, leaf->right());
		}
		else {
			leaf->set_right(new treeNode(key));
		}
	}
}

treeNode* binaryTree::search(String key, treeNode* leaf)
{
	if (leaf)
	{
		if (key == leaf->value())
		{
			return leaf;
		}
		if (key < leaf->value())
		{
			return search(key, leaf->left());
		}
		else
		{
			return search(key, leaf->right());
		}
	}
	else
	{
		return nullptr;
	}
}

treeNode* binaryTree::remove(String key, treeNode* leaf)
{
	treeNode* temp;
	if (!leaf)
	{
		return nullptr;
	}
	else if (key < leaf->value())
	{
		leaf->set_left(remove(key, leaf->left()));
	}
	else if (key > leaf->value())
	{
		leaf->set_right(remove(key, leaf->right()));
	}
	else if (leaf->left() && leaf->right())
	{
		temp = findMin(leaf->right());
		leaf->setValue(temp->value());
		leaf->set_right(remove(leaf->value(), leaf->right()));
	}
	else
	{
		temp = leaf;
		if (!leaf->left())
		{
			leaf = leaf->right();
		}
		else if (!leaf->right())
		{
			leaf = leaf->left();
		}
		temp->set_left(nullptr);
		temp->set_right(nullptr);
		delete temp;
	}

	return leaf;
}

treeNode* binaryTree::findMin(treeNode* leaf)
{
	if (!leaf)
	{
		return NULL;
	}
	else if (!leaf->left())
	{
		return leaf;
	}
	else
	{
		return findMin(leaf->left());
	}
}

void binaryTree::inorder(const Function& f, treeNode* leaf)
{
	if (leaf)
	{
		inorder(f, leaf->left());
		leaf->setValue(f(leaf->value()));
		inorder(f, leaf->right());
	}
}

void binaryTree::postorder(const Function& f, treeNode* leaf)
{
	if (leaf)
	{
		postorder(f, leaf->left());
		postorder(f, leaf->right());
		leaf->setValue(f(leaf->value()));
	}
}

void binaryTree::preorder(const Function& f, treeNode* leaf)
{
	if (leaf)
	{
		leaf->setValue(f(leaf->value()));
		postorder(f, leaf->left());
		postorder(f, leaf->right());
	}
}
