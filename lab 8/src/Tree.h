#pragma once
#include <iostream>
#include <iomanip>

template<typename T>
class Tree
{
public:
	struct Node
	{
		T data;
		Node* child = nullptr;
		Node* brother = nullptr;

		Node(const T& obj, Node* next = nullptr)
			: data(obj), brother(next) {}

		~Node()
		{
			delete child;
		}
	};

	/// <summary>
	/// 
	/// </summary>
	/// <param name="path">: array of indeñes of childs with size that equal depth param.variable</param>
	void add(const T& obj,
		size_t depth = 0, size_t* path = nullptr)
	{
		if (root == nullptr)
		{
			root = new Node(obj);
			return;
		}

		Node* cur = root;
		for (size_t i = 0; i < depth; i++)
		{
			cur = cur->child;
			for (size_t j = 0; j < path[i]; j++)
			{
				cur = cur->brother;
			}
		}
		cur->child = new Node(obj, cur->child);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <returns>0 if removed</returns>
	bool remove(const T& obj)
	{
		if(obj == root->data)
		{
			delete root;
			return 0;
		}
		return find_and_remove(root, obj);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="obj"></param>
	/// <returns>Addres of element if found. nullptr otherwise.</returns>
	T* find(const T& obj, int type)
	{
		switch (type)
		{
		case 0:
			return pre_find(root, obj);
		case 1:
			return post_find(root, obj);
		case 2:
			return in_find(root, obj);
		}
	}

	void print() const
	{
		if (root == nullptr) { return; }
		print_with_root(root);
	}
private:
	T* pre_find(Node* root, const T& obj)
	{
		Node* cur = root;
		do
		{
			std::cout << cur->data << ", ";
			if (cur->data == obj)
			{
				return &cur->data;
			}
			if (cur->child != nullptr)
			{
				T* r = pre_find(cur->child, obj);
				if (r != nullptr)
				{
					return r;
				}
			}
			
			cur = cur->brother;
		} while (cur != nullptr);

		return nullptr;
	}

	T* post_find(Node* root, const T& obj)
	{
		Node* cur = root;
		do
		{
			if (cur->child != nullptr)
			{
				T* r = post_find(cur->child, obj);
				if (r != nullptr)
				{
					return r;
				}
			}
			std::cout << cur->data << ", ";
			if (cur->data == obj)
			{
				return &cur->data;
			}
			cur = cur->brother;
		} while (cur != nullptr);

		return nullptr;
	}

	T* in_find(Node* root, const T& obj, bool left = false)
	{
		Node* cur = root;
		
		if (cur->child != nullptr)
		{
			T* r = in_find(cur->child, obj, true);
			if (r != nullptr)
			{
				return r;
			}
		}
		std::cout << cur->data << ", ";
		if (cur->data == obj)
		{
			return &cur->data;
		}
		do
		{
			if (cur->child != nullptr && cur->child->brother != nullptr)
			{
				T* r = in_find(cur->child->brother, obj);
				if (r != nullptr)
				{
					return r;
				}
			}
			if (left)
			{
				break;
			}
			cur = cur->brother;
			if (cur != nullptr) {
				T* r = in_find(cur, obj);
				if (r != nullptr)
				{
					return r;
				}
			}
		} while (cur != nullptr);

		return nullptr;
	}

	bool find_and_remove(Node* root, const T& obj)
	{
		Node* cur = root;
		while (cur->brother != nullptr)
		{
			if (cur->brother->data == obj)
			{
				Node* tmp = cur->brother->brother;
				delete cur->brother;
				cur->brother = tmp;
				return 0;
			}
			cur = cur->brother;
		} 

		cur = root;
		do
		{
			if (cur->child != nullptr)
			{
				if (cur->child->data == obj)
				{
					Node* tmp = cur->child->brother;
					delete cur->child;
					cur->child = tmp;
					return 0;
				}
				if(find_and_remove(cur->child, obj) == 0)
				{
					return 0;
				}
			}
			cur = cur->brother;
		} while (cur != nullptr);

		return 1;
	}

	void print_with_root(Node* root, int depth = 0, bool last = false) const
	{
		Node* cur = root;
		do
		{
			if (depth > 0)
			{
			for (size_t i = 0; i < (depth > 0 ? depth - 1 : depth); i++)
			{
				std::cout << "|   ";
			}
			
			std::cout << '|' << "---";
			}
			std::cout << cur->data << "\n";
			if (cur->child != nullptr)
			{
				print_with_root(cur->child, depth + 1);
			}
			cur = cur->brother;
		} while (cur != nullptr);
		
		for (size_t i = 0; i < (depth > 0 ? depth - 1 : depth); i++)
		{
			std::cout << "|   ";
		}
		std::cout << '\n';
	}

	Node* root = nullptr;
};

