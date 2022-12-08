#pragma once
#include <iostream>

template<typename T>
class AVLTree
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

	void add(const T& obj)
	{
		if (root == nullptr)
		{
			root = new Node(obj);
			return;
		}
		Node** cur = &root;
		while (true)
		{
			if ((*cur) == nullptr)
			{
				(*cur) = new Node(obj);
				break;
			}
			if ((*cur)->data == obj)
			{
				throw std::invalid_argument("Element already exist");
			}
			cur = &(obj > (*cur)->data ? (*cur)->right : (*cur)->left);
		}

		balance(&root);
	}

	bool remove(const T& obj)
	{
		if (root->data == obj)
		{
			remove_node(&root);
			balance(&root);
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
					balance(&root);
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

	void print() const
	{
		if (root == nullptr) { return; }
		print_with_root(root);
	}

private:
	int balance(Node** pRoot)
	{
		Node* root = *pRoot;
		if (root == nullptr)
		{
			return -1;
		}
		int l_height = balance(&root->left);
		int r_height = balance(&root->right);
		int balance_factor = l_height - r_height;

		if (balance_factor > 1)
		{
			if (get_height(root->left->left) >= get_height(root->left->right))
			{
				*pRoot = rotate(root, true);
			}
			else
			{
				*pRoot = rotate(root, true, true);
			}
			l_height--; r_height--;
		}
		else if (balance_factor < -1)
		{
			if (get_height(root->right->left) <= get_height(root->right->right))
			{
				*pRoot = rotate(root, false);
			}
			else
			{
				*pRoot = rotate(root, false, true);
			}
			l_height--; r_height--;
		}
		return std::max(l_height, r_height) + 1;
	}

	Node* rotate(Node* root, bool right, bool big = false)
	{
		if (big)
		{
			if (right)
			{
				root->left = rotate(root->left, false);
			}
			else
			{
				root->right = rotate(root->right, true);
			}
		}

		Node* new_root;
		if (right)
		{
			new_root = root->left;
			root->left = new_root->right;
			new_root->right = root;
		}
		else
		{
			new_root = root->right;
			root->right = new_root->left;
			new_root->left = root;
		}
		
		return new_root;
	}

	int get_height(Node* root)
	{
		if (root == nullptr)
		{
			return -1;
		}
		return std::max(get_height(root->left), get_height(root->right)) + 1;
	}

	int get_balance(Node* node)
	{
		if (node == nullptr)
		{
			return -1;
		}

		return get_balance(node->left) - get_balance(node->right);
	}

	void print_with_root(Node* root, int depth = 1, bool left = false) const
	{
		Node* cur = root;

		if (cur->right != nullptr)
		{
			print_with_root(cur->right, depth + 1);
		}
		std::cout << std::endl << std::string(4 * (depth - 1), ' ') << (left ? 'L' : 'R') << root->data << std::endl;
		if (cur->left != nullptr)
		{
			print_with_root(cur->left, depth + 1, true);
		}
	}

	void remove_node(Node** pRoot)
	{
		Node* rem_root = *pRoot;
		if (rem_root->right && rem_root->left)
		{
			if (rem_root->left->right != nullptr)
			{
				Node** cur = &rem_root->left->right;
				while ((*cur)->right != nullptr)
				{
					cur = &(*cur)->right;
				}
				rem_root->data = std::move((*cur)->data);
				if ((*cur)->left != nullptr)
				{
					(*cur)->data = std::move((*cur)->left->data);
					delete (*cur)->left;
					(*cur)->left = nullptr;
				}
				else
				{
					delete* cur;
					*cur = nullptr;
				}
			}
			else
			{
				rem_root->data = std::move(rem_root->left->data);
				Node* tmp = rem_root->left->left;
				delete rem_root->left;
				rem_root->left = tmp;
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
	
	Node* root = nullptr;
};