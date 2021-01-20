#include "templatedBinaryTree.h"

#include <iostream>

using namespace std;

int main()
{
	templatedBinaryTree<int>* tree = new templatedBinaryTree<int>();

	tree->insert(10);
	tree->insert(6);
	tree->insert(14);
	tree->insert(5);
	tree->insert(8);
	tree->insert(11);
	tree->insert(18);

	std::function<int(const int&)> f = [](const int& v) -> int
	{
		cout << v << ' ';
		return v;
	};

	tree->preorder(f);
	cout << '\n';
	tree->inorder(f);
	cout << '\n';
	tree->postorder(f);
	cout << '\n';

	tree->remove(8);

	tree->preorder(f);
	cout << '\n';
	tree->inorder(f);
	cout << '\n';
	tree->postorder(f);
	cout << '\n';

	tree->remove(14);

	tree->preorder(f);
	cout << '\n';
	tree->inorder(f);
	cout << '\n';
	tree->postorder(f);
	cout << '\n';

	tree->remove(6);

	tree->preorder(f);
	cout << '\n';
	tree->inorder(f);
	cout << '\n';
	tree->postorder(f);
	cout << '\n';

	delete tree;

}