#pragma once

#pragma once

#include "templatedTreeNode.h"
#include <functional>

template<class T>
class templatedBinaryTree
{
public:
	typedef std::function<T(const T&)> Function;

	templatedBinaryTree() : m_root(nullptr) {}
	~templatedBinaryTree()
	{
		if (m_root)
		{
			m_root->~TemplatedTreeNode<T>();
		}
	}

	void insert(T key)
	{
		if (m_root)
		{
			insert(key, m_root);
		}
		else
		{
			m_root = new TemplatedTreeNode<T>(key);
		}
	}

	TemplatedTreeNode<T>* search(T key)
	{
		return search(key, m_root);
	}
	void remove(T key)
	{
		remove(key, m_root);
	}
	void clear()
	{
		this->~templatedBinaryTree();
		m_root = nullptr;
	}

	void inorder(const Function& f)
	{
		inorder(f, m_root);
	}
	void postorder(const Function& f)
	{
		postorder(f, m_root);
	}
	void preorder(const Function& f)
	{
		preorder(f, m_root);
	}

private:
	void insert(T key, TemplatedTreeNode<T>* leaf)
	{
		if (key < leaf->value())
		{
			if (leaf->left())
			{
				insert(key, leaf->left());
			}
			else
			{
				leaf->set_left(new TemplatedTreeNode<T>(key));
			}
		}
		else if (key >= leaf->value())
		{
			if (leaf->right())
			{
				insert(key, leaf->right());
			}
			else {
				leaf->set_right(new TemplatedTreeNode<T>(key));
			}
		}
	}

	TemplatedTreeNode<T>* search(T key, TemplatedTreeNode<T>* leaf)
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
	TemplatedTreeNode<T>* remove(T key, TemplatedTreeNode<T>* leaf)
	{
		TemplatedTreeNode<T>* temp;
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

	TemplatedTreeNode<T>* findMin(TemplatedTreeNode<T>* leaf)
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

	void inorder(const Function& f, TemplatedTreeNode<T>* leaf)
	{
		if (leaf)
		{
			inorder(f, leaf->left());
			leaf->setValue(f(leaf->value()));
			inorder(f, leaf->right());
		}
	}
	void postorder(const Function& f, TemplatedTreeNode<T>* leaf)
	{
		if (leaf)
		{
			postorder(f, leaf->left());
			postorder(f, leaf->right());
			leaf->setValue(f(leaf->value()));
		}
	}
	void preorder(const Function& f, TemplatedTreeNode<T>* leaf)
	{
		if (leaf)
		{
			leaf->setValue(f(leaf->value()));
			postorder(f, leaf->left());
			postorder(f, leaf->right());
		}
	}

	TemplatedTreeNode<T>* m_root;
};