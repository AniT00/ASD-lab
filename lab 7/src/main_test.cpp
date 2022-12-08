#include "HashTable.h"

int main(int argc, char** argv)
{
	HashTable<int> table(3);

	table.add(5, 5);
	table.print();
	table.add(8, 8);
	table.print();
	table.add(9, 9);
	table.print();
	table.add(2, 2);
	table.print();
	table.add(11, 11);
	table.print();
	table.add(23, 23);
	table.print();

	table.add(0, 0);
	table.print();

	table.remove(11);
	table.print();

	int* p = table.find(11);
	if (p == nullptr)
		std::cout << "No element with key 11";
	else
		std::cout << "Element value is " << *p;
	std::cout << '\n';

	p = table.find(23);
	if (p == nullptr)
		std::cout << "No element with key 23";
	else
		std::cout << "Element value is " << *p;
	std::cout << '\n';

	table.remove(0);
	table.print();

	p = table.find(0);
	if (p == nullptr)
		std::cout << "No element with key 0";
	else
		std::cout << "Element value is " << *p;
	std::cout << '\n';

	table.add(1, 1);
	table.print();

	table.add(13, 13);
	table.print();

	table.add(25, 25);
	table.print();

	p = table.find(25);
	if (p == nullptr)
		std::cout << "No element with key 25";
	else
		std::cout << "Element value is " << *p;
	std::cout << '\n';

	return 0;
}