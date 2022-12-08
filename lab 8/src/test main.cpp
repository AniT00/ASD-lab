#include <iostream>
#include <string>
#include <iomanip>
#include "Tree.h"

using namespace std;

int main()
{
	Tree<int> tree;

	tree.add(5);
	tree.add(2);
	tree.add(3);
	tree.add(4);
	size_t p[100];
	p[0] = 0;
	tree.add(1, 1, p);
	p[0] = 1;
	tree.add(7, 1, p);
	tree.add(9, 1, p);
	p[0] = 1;
	p[1] = 0;
	tree.add(0, 2, p);
	p[0] = 1;
	p[1] = 1;
	tree.add(6, 2, p);
	tree.add(8, 2, p);

	tree.print();

	cout << "Pre-order: ";
	tree.find(10, 0);
	cout << "\nPost-order: ";
	tree.find(10, 1);
	cout << "\nIn-order: ";
	tree.find(10, 2);

	return 0;
}