#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include <exception>
#include <utility>

template<typename T>
class HashTable
{
public:
	HashTable()
	{
		table_size = 5;
		max_fill = max_fill_percent * table_size;
		table = new std::pair<int, T>*[table_size] { nullptr };
	}

	HashTable(size_t _size)
	{
		table_size = _size;
		max_fill = max_fill_percent * table_size;
		table = new std::pair<int, T>*[table_size] { nullptr };
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="key"></param>
	/// <param name="value"></param>
	/// <returns>0 if element added. 1 if already exist</returns>
	bool add(int key, const T& value)
	{
		int hash = getHash(key);

		for (size_t i = hash; i < hash + table_size; i++)
		{
			if (table[i % table_size] == nullptr)
			{
				table[i % table_size] = new std::pair<int, T>(key, value);
				fill_count++;
				break;
			}
			else if (table[i % table_size]->first == key)
			{
				return 1;
			}
		}
		if (fill_count >= max_fill)
		{
			resize();
			
		}
		return 0;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="key"></param>
	/// <returns>0 if element is removed, 1 otherwise.</returns>
	bool remove(int key)
	{
		int hash = getHash(key);
		for (size_t i = hash; i < hash + table_size; i++)
		{
			if (table[i % table_size] != nullptr)
			{
				if (table[i % table_size]->first == key)
				{
					delete table[i % table_size];
					table[i % table_size] = nullptr;
					fill_count--;
					return 0;
				}
			}
		}
		return 1;
	}

	T* find(int key)
	{
		int hash = getHash(key);
		
		for (size_t i = hash; i < table_size; i++)
		{
			if (table[i] != nullptr)
			{
				if (table[i]->first == key)
				{
					return &table[i]->second;
				}
			}
		}
		return nullptr;
	}

	void print()
	{
		for (size_t i = 0; i < table_size; i++)
		{
			if (table[i] != nullptr)
			{
				std::cout << std::setw(3) << table[i]->second;
			}
			else
			{
				std::cout << std::setw(3) << '_';
			}
		}
		std::cout << "\n\n";
	}

	~HashTable()
	{
		for (size_t i = 0; i < table_size; i++)
		{
			if (table[i] != nullptr)
			{
				delete table[i];
			}
		}
		delete[] table;

	}

private:
	int getHash(int val)
	{
		return val % table_size;
	}

	void resize()
	{
		HashTable tmp(table_size * 2);
		for (size_t i = 0; i < table_size; i++)
		{
			if (table[i] != nullptr)
			{
				int hash = getHash(table[i]->first);
				auto p = table[i];
				tmp.add(p->first, p->second);
			}
		}
		std::swap(table, tmp.table);
		std::swap(table_size, tmp.table_size);
		std::swap(max_fill, tmp.max_fill);
	}
	
	static const float max_fill_percent;

	std::pair<int, T>** table;

	size_t table_size;

	int fill_count = 0;

	float max_fill;
};

template<typename T>
const float HashTable<T>::max_fill_percent = 0.75;