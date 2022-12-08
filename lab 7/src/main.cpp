#include <iostream>
#include <string>
#include <functional>
#include <iomanip>
#include <cmath>
#include "HashTable.h"

using namespace std;

void callMenu();

template<typename T>
void inputWithValidation(
	T* data_ptr,
	const  string& invitation_msg,
	const  string& error_msg,
	type_identity_t< function<bool(T&)>> condition);

int main()
{
	callMenu();
	return 0;
}

void callMenu()
{
	HashTable<string> table(3);
	table.add(1, "1");
	table.print();
	table.add(2, "2");
	table.print();
	table.add(0, "0");
	/*table.print();
	table.add(5, "5");
	table.print();
	table.add(23, "23");
	table.print();
	table.add(5, "5");
	table.add(3, "3");
	table.print();
	table.print();
	table.add(21, "21");
	table.print();
	
	table.add(25, "25");
	table.print();*/

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

		table.print();
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
			int key;
			string s;
			cout << "Enter key value: ";
			cin >> key;
			cout << "Enter string value: ";
			cin.ignore();
			getline(cin, s);
			
			if(table.add(key, s))
			{
				cout << "Element with this key already exist.\n";
			}
		}
		break;
		case REMOVE:
		{
			int key;
			cout << "Enter key of element to remove: ";
			cin >> key;
			if (table.remove(key))
			{
				cout << "No element with such key." << endl;
			}
		}
		break;
		case FIND:
		{
			int key;
			cout << "Enter key of element to find: ";
			cin >> key;
			string* found_string = table.find(key);
			if (found_string != nullptr)
				cout << "Found: " << *found_string;
			else
				cout << "No such element\n";
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


template<typename T>
void inputWithValidation(
	T* data_ptr,
	const  string& invitation_msg,
	const  string& error_msg,
	type_identity_t< function<bool(T&)>> condition)
{
	do
	{
		cout << invitation_msg;
		cin >> *data_ptr;
		cin.ignore(INT_MAX, '\n');
	} while (!(condition(*data_ptr) || !(cout << error_msg << endl)));
}
