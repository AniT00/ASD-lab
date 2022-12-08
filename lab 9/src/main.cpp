#include <iostream>
#include <string>
#include <iomanip>
#include "BinTree.h"

using namespace std;

void callMenu();

int main()
{
	callMenu();
	return 0;
}

void callMenu()
{
	BinTree<int> tree;

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
		switch (inp)
		{
		case ADD:
		{
			int value;
			cout << "Enter value: ";
			cin >> value;
			tree.add(value);
		}
		break;
		case REMOVE:
		{
			int value;
			cout << "Enter value of element to remove: ";
			cin >> value;

			tree.remove(value);
		}
		break;
		case FIND:
		{
			int key;
			cout << "Enter value of element to find: ";
			cin >> key;
			if (tree.find(key))
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
