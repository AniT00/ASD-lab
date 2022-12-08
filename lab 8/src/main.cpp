#include <iostream>
#include <string>
#include <iomanip>
#include "Tree.h"

using namespace std;

void callMenu();

int main()
{
	callMenu();
	return 0;
}

void callMenu()
{
	Tree<int> tree;

	enum MenuOptions {
		ADD,
		REMOVE,
		FIND,
		EXIT,
		MENU_OPTIONS_COUNT
	};

	string menu_options_text[]
	{
		"Add element",
		"Remove element",
		"Find element",
		"Exit"
	};

	while (true) {
		int inp = 0;

		tree.print();

		cout << "Enter the number of command to execute:\n";
		for (size_t i = 0; i < MENU_OPTIONS_COUNT; i++)
		{
			cout << setw(3) << i << ". " << menu_options_text[i] << endl;
		}
		cin >> inp;

		system("cls");
		switch (inp)
		{
		case ADD:
		{
			tree.print();
			int value;
			cout << "Enter value: ";
			cin >> value;
			size_t depth;
			cout << "Enter depth: ";
			cin >> depth;
			size_t* path = new size_t[depth];
			cout << "Enter depth: ";
			for (size_t i = 0; i < depth; i++)
			{
				cout << "Layer " << i << ": ";
				cin >> path[i];
			}
			tree.add(value, depth, path);
		}
		break;
		case REMOVE:
		{
			tree.print();
			int value;
			cout << "Enter value of element to remove: ";
			cin >> value;

			tree.remove(value);
		}
		break;
		case FIND:
		{
			tree.print();
			int key;
			cout << "Enter value of element to find: ";
			cin >> key;
			int type;
			cout << "0. Pre-order\n"
				<< "1. Post-order\n"
				<< "2. In-order\n"
				<< "Enter type: ";
			cin >> type;
			if (tree.find(key, type))
				cout << "\nElement exist.\n";
			else
				cout << "\nNo such element.\n";
		}
		break;
		case EXIT:
			return;
		default:
			cout << "\nInvalid input! Try again.";
			break;
		}
		system("pause");
		system("cls");
	}
}
