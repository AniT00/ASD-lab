#include <iostream>
#include <string>
#include <iomanip>
#include "BinTree.h"

using namespace std;

template<typename T>
void find(const BinTree<T>& tree, const T& obj)
{
	cout << (tree.find(obj)  == nullptr ? "No such elemnt.\n" : "Element found.\n");
}

template<typename T>
void remove(BinTree<T>& tree, const T& obj)
{
	cout << (tree.remove(obj) == 0 ? "Element removed: " : "Element not found: ") << obj << '\n';
	tree.print();
}

int main()
{
	BinTree<int> tree;
	tree.add(5);
	tree.add(2);
	tree.add(8);
	tree.add(9);
	tree.add(6);
	tree.add(1);
	tree.add(7);
	tree.add(4);
	tree.add(3);
	tree.add(0);
	tree.print();

	remove(tree, 0);
	find(tree, 0);

	find(tree, 9);
	remove(tree, 8);
	remove(tree, 2);
	find(tree, 2);
	find(tree, 8);
	remove(tree, 9);
	tree.add(8);
	tree.print();
	remove(tree, 5);
	find(tree, 5);
	find(tree, 8);

	return 0;
}