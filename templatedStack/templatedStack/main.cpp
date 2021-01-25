#include "stack.h"
#include <iostream>

using namespace std;

int main()
{
	Stack<int> s;
	s.push(6);
	s.push(7);
	s.push(5);
	s.push(9);
	s.push(0);

	cout << "peek " << s.peek() << '\n';

	cout << "size " << s.size() << '\n';

	cout << "pop\n";
	while (s.size())
	{
		cout << s.pop() << '\n';
	}
}