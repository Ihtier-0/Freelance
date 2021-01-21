#include "templatedBinaryTree.h"
#include "String.h"

#include <iostream>

using namespace std;

int main()
{
	templatedBinaryTree<String>* tree = new templatedBinaryTree<String>();

	tree->insert("c");
	tree->insert("d");
	tree->insert("e");
	tree->insert("a");
	tree->insert("b");

	std::function<String(const String&)> f = [](const String& v) -> String
	{
		v.print();
		return v;
	};

	tree->preorder(f);
	cout << '\n';
	tree->inorder(f);
	cout << '\n';
	tree->postorder(f);
	cout << '\n';

	tree->remove("c");

	cout << "remove c:\n";
	tree->preorder(f);
	cout << '\n';
	tree->inorder(f);
	cout << '\n';
	tree->postorder(f);
	cout << '\n';

	tree->remove("a");

	cout << "remove a:\n";
	tree->preorder(f);
	cout << '\n';
	tree->inorder(f);
	cout << '\n';
	tree->postorder(f);
	cout << '\n';

	tree->remove("d");

	cout << "remove d:\n";
	tree->preorder(f);
	cout << '\n';
	tree->inorder(f);
	cout << '\n';
	tree->postorder(f);
	cout << '\n';

	delete tree;

}