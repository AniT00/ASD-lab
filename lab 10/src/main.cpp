#include "AVLTree.h"

#include <string>
#include <iomanip>

using namespace std;

void add(AVLTree<int>& tree, int* arr, int length)
{
	for (size_t i = 0; i < length; i++)
	{
		tree.add(arr[i]);
		system("cls");
		tree.print();
		//system("pause");

	}
}

void remove(AVLTree<int>& tree, int* arr, int length)
{
	for (size_t i = 0; i < length; i++)
	{
		tree.remove(arr[i]);
		system("cls");
		tree.print();
		//system("pause");

	}
}

void callMenu();

int main()
{
	callMenu();
	return 0;
}

void callMenu()
{
	AVLTree<int> tree;
	int arr[] = { 5, 2, 8, 1, 3, 7, 10, 9, 0, 4, 11, 15, 20,
		25, 30, 35, 40, 45, 12, 50, 55, 60, 65, 70, 75, 80, 85, 29, 21, 22, 23 };

	int r_arr[] = { 29, 20, 4, 3, 70, 15, 25, 23, 11, 12, 21 };
	int size = sizeof(arr) / sizeof(int);
	int r_size = sizeof(r_arr) / sizeof(int);

	add(tree, arr, size);
	remove(tree, r_arr, r_size);

	enum MenuOptions {
		ADD,
		REMOVE,
		EXIT,
		MENU_OPTIONS_COUNT
	};

	string menu_options_text[]
	{

		"Add element",
		"Remove element",
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
