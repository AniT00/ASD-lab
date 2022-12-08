#pragma once
#include <iostream>
#include <cmath>
#include <exception>
#include <utility>

template<typename T>
class HashTable
{
public:
	struct node
	{
		node* next;
		std::pair<int, T> data;

		node(const std::pair<int, T> obj, node* _next = nullptr)
			: data(obj)
		{
			next = _next;
		}
	};

	HashTable()
	{
		table_size = 5;
		table = new node * [table_size] { 0 };
	}

	HashTable(size_t _size)
	{
		table_size = _size;
		table = new node * [table_size] { 0 };
	}

	bool add(int key, const T& value)
	{
		int hash = getHash(key);
		node* cur = table[hash];
		if (cur != nullptr)
		{
			while (true)
			{
				if (cur->data.first == key)
				{
					return 1;
				}
				if (cur->next != nullptr)
				{
					cur = cur->next;
				}
				else
				{
					break;
				}
			} 
		}
		std::pair<int, T> d(key, value);
		table[hash] = new node(d, table[hash]);
		return 0;
	}

	bool remove(int key)
	{
		int hash = getHash(key);
		node* cur = table[hash];
		if (cur != nullptr)
		{
			if (cur->data.first == key)
			{
				node* tmp = cur->next;
				delete cur;
				table[hash] = tmp;
				return 0;
			}
			while (cur->next != nullptr)
			{
				if (cur->next->data.first == key)
				{
					node* tmp = cur->next->next;
					delete cur->next;
					cur->next = tmp;
					return 0;
				}
				cur = cur->next;
			}
		}
		return 1;
	}

	T* find(int key)
	{
		int hash = getHash(key);
		node* cur = table[hash];
		while (cur != nullptr)
		{
			if (cur->data.first == key)
			{
				return &cur->data.second;
			}
			cur = cur->next;
		}
		return nullptr;
	}

	void print()
	{
		for (size_t i = 0; i < table_size; i++)
		{
			node* cur = table[i];
			std::cout << i << ": ";
			while (cur != nullptr)
			{
				std::cout << " -> " << cur->data.second;
				cur = cur->next;
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}

	~HashTable()
	{
		for (size_t i = 0; i < table_size; i++)
		{
			node* cur = table[i];
			while (cur != nullptr)
			{
				node* tmp = cur->next;
				delete cur;
				cur = tmp;
			}
		}
		delete[] table;
	}

private:
	int getHash(int val)
	{
		return val % table_size;
	}

	node** table;

	size_t table_size;
};

