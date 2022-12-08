#pragma once
#include <iostream>
#include <iomanip>

template<typename T>
class BinTree
{
public:
	struct Node
	{
		T data;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(const T& obj)
			: data(obj) {}
	};

	/// <summary>
	/// 
	/// </summary>
	/// <param name="obj"></param>
	/// <returns>0 if already exist.</returns>
	int add(const T& obj)
	{
		if (root == nullptr)
		{
			root = new Node(obj);
			return 1;
		}
		Node* cur = root;
		while (true)
		{
			if (obj == cur->data)
			{
				return 0;
			}
			Node** tmp = obj > cur->data ? &cur->right : &cur->left;
			if (*tmp != nullptr)
			{
				cur = *tmp;
			}
			else
			{
				*tmp = new Node(obj);
				return 1;
			}
		}
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="obj"></param>
	/// <returns>0 if removed.</returns>
	int remove(const T& obj)
	{
		if (root->data == obj)
		{
			remove_node(&root);
			return 0;
		}
		Node* cur = root;
		while (true)
		{
			Node** tmp = obj > cur->data ? &cur->right : &cur->left;
			if (*tmp != nullptr)
			{
				if ((*tmp)->data == obj)
				{
					remove_node(tmp);
					return 0;
				}
				else
				{
					cur = *tmp;
				}
			}
			else
			{
				return 1;
			}
		}
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="obj"></param>
	/// <returns>Addres of element if found. nullptr otherwise.</returns>
	T* find(const T& obj) const
	{
		Node* cur = root;
		if (cur != nullptr)
		{
			while (true)
			{
				if (obj == cur->data)
				{
					return &cur->data;
				}
				Node** tmp = obj > cur->data ? &cur->right : &cur->left;
				if (*tmp != nullptr)
				{
					cur = *tmp;
				}
				else
				{
					return nullptr;
				}
			}
		}
	}

	void print() const
	{
		if (root == nullptr) { return; }
		print_with_root(root);
	}

private:
	void remove_node(Node** pRoot)
	{
		Node* rem_root = *pRoot;
		if(rem_root->right && rem_root->left)
		{
			if (rem_root->right->left != nullptr)
			{
				Node** cur = &rem_root->right->left;
				while ((*cur)->left != nullptr)
				{
					cur = &(*cur)->left;
				}
				rem_root->data = std::move((*cur)->data);
				if ((*cur)->right != nullptr)
				{
					(*cur)->data = std::move((*cur)->right->data);
					delete (*cur)->right;
					(*cur)->right = nullptr;
				}
				else
				{
					delete *cur;
					*cur = nullptr;
				}
			}
			else
			{
				rem_root->data = std::move(rem_root->right->data);
				Node* tmp = rem_root->right->right;
				delete rem_root->right;
				rem_root->right = tmp;
			}
		}
		else if (rem_root->left || rem_root->right)
		{
			Node* t = rem_root->left != nullptr ? rem_root->left : rem_root->right;
			*pRoot = t;
			delete rem_root;
			rem_root = nullptr;
		}
		else
		{
			delete rem_root;
			*pRoot = nullptr;
		}
	}
	
	void print_with_root(Node* root, int depth = 1, bool left = false) const
	{
		Node* cur = root;

		if (cur->right != nullptr)
		{
			print_with_root(cur->right, depth + 1);
		}
		std::cout << std::endl << std::string(4 * (depth - 1), ' ') << (left ? 'L' :'R') << root->data << std::endl;
		if (cur->left != nullptr)
		{
			print_with_root(cur->left, depth + 1, true);
		}
	}

	Node* root = nullptr;
};

