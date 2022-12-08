#pragma once
#include <iostream>
#include <fstream>
#define NOMINMAX
#include <Windows.h>

template<typename T>
class RBTree;

template<typename T>
std::ostream& operator<<(std::ostream& os, const RBTree<T>& obj);

template<typename T>
class RBTree
{
public:
	struct Node
	{
		T data;
		Node* left = nullptr;
		Node* right = nullptr;
		bool black = false;

		Node(const T& obj)
			: data(obj)
		{
		}
	};

	enum class BalanceStatus
	{
		CHECK_ROOT,
		TREE_BALANCED,
		BALANCE_ROOT,
		BALANCE_REPLACED_ROOT
	};

	void add(const T& obj)
	{
		BalanceStatus result = insert(&root, obj);
		root->black = true;
	}

	void remove(const T& obj)
	{
		remove_if_equales(&root, obj);
		if (root != nullptr)
		{
			root->black = true;
		}
	}

	void print() const
	{
		if (root == nullptr)
		{
			return;
		}
		print_with_root(std::cout, root);
	}


	~RBTree()
	{
		if (root != nullptr)
		{
			clear_root(root);
		}
	}

private:

	BalanceStatus remove_if_equales(Node** p_rem_node, const T& obj)
	{
		Node* rem_node = *p_rem_node;
		BalanceStatus result;
		if (obj == rem_node->data)
		{
			if (rem_node->right && rem_node->left)
			{
				result = change_to_largest(&rem_node->left, p_rem_node);			
				rem_node = *p_rem_node;
			}
			else if (rem_node->left || rem_node->right)
			{
				Node* tmp = rem_node;
				*p_rem_node = rem_node->left != nullptr ? rem_node->left : rem_node->right;
				(*p_rem_node)->black = true;
				delete tmp;
				return BalanceStatus::TREE_BALANCED;
				/*bool black = t->black;
				t->black = (*p_rem_node)->black;
				*p_rem_node = t;
				delete rem_node;
				rem_node = nullptr;
				return black ? BalanceStatus::BALANCE_ROOT : BalanceStatus::TREE_BALANCED;*/
			}
			else
			{
				bool black = rem_node->black;
				delete rem_node;
				*p_rem_node = nullptr;
				return black ? BalanceStatus::BALANCE_ROOT : BalanceStatus::TREE_BALANCED;
			}
		}
		else
		{
			 result = remove_if_equales(&(obj > rem_node->data ? rem_node->right : rem_node->left), obj);
		}

		switch (result)
		{
		case BalanceStatus::TREE_BALANCED:
			return BalanceStatus::TREE_BALANCED;
			break;
		// When this root was removed, had two childs and got replaced.
		case BalanceStatus::BALANCE_REPLACED_ROOT:
		{
			Node* father = rem_node->left;
			Node* brother = rem_node->right;
			// 1 case
			if (/*(*root)->left != nullptr && */!brother->black)
			{
				*p_rem_node = rotate(*p_rem_node, false);
				rem_node->black = true;
				father->black = false;
				return BalanceStatus::TREE_BALANCED;
			}
			else // 2 case
			{
				// If right is red
				if ((brother->right != nullptr && !brother->right->black))
				{
					// â
					brother->black = rem_node->black;
					brother->right->black = rem_node->black = true;
					*p_rem_node = rotate(rem_node, false);
					return BalanceStatus::TREE_BALANCED;
				}
				// If left is red
				else if ((brother->left != nullptr && !brother->left->black))
				{
					// á
					brother->black = false;
					brother->left->black = true;
					rem_node->right = rotate(brother, true);
					return BalanceStatus::TREE_BALANCED;
				}
				else
				{
					// à
					brother->black = false;
					return BalanceStatus::BALANCE_ROOT;
				}
			}
			break;
		}
		case BalanceStatus::BALANCE_ROOT:
		{
			Node* father;
			Node** brother;
			Node* distant_nephew;
			Node* close_nephew;
			bool f_right = obj > rem_node->data;
			if (f_right)
			{
				father = rem_node->right;
				brother = &rem_node->left;
				distant_nephew = (*brother)->left;
				close_nephew = (*brother)->right;
			}
			else
			{
				father = rem_node->left;
				brother = &rem_node->right;
				distant_nephew = (*brother)->right;
				close_nephew = (*brother)->left;
			}
			if (/*(*root)->left != nullptr && */!(*brother)->black)
			{
				*p_rem_node = rotate(*p_rem_node, f_right);
				rem_node->black = true;
				father->black = false;
				return BalanceStatus::TREE_BALANCED;
			}
			else
			{
				// If distant_nephew is red
				if ((distant_nephew != nullptr && !distant_nephew->black))
				{
					// â
					(*brother)->black = rem_node->black;
					distant_nephew->black = rem_node->black = true;
					*p_rem_node = rotate(rem_node, f_right);
					return BalanceStatus::TREE_BALANCED;
				}
				// If distant_nephew uncle is red
				else if ((close_nephew != nullptr && !close_nephew->black))
				{
					// á
					(*brother)->black = false;
					close_nephew->black = true;
					*brother = rotate(*brother, !f_right);
					return BalanceStatus::TREE_BALANCED;
				}
				else
				{
					// à
					(*brother)->black = false;
					return BalanceStatus::BALANCE_ROOT;
				}
			}
		}
		break;
		default:
			throw;
			break;
		}
	}

	BalanceStatus change_to_largest(Node** root, Node** node_to_change)
	{
		if ((*root)->right == nullptr)
		{
			Node* largest = *root;
			(*root) = nullptr;
			Node* left = (*node_to_change)->left;
			Node* right = (*node_to_change)->right;
			bool black = (*node_to_change)->black;
			bool rem_black = largest->black;
			delete *node_to_change;
			*node_to_change = largest;
			(*node_to_change)->left = left;
			(*node_to_change)->right = right;
			(*node_to_change)->black = black;

			return rem_black ? BalanceStatus::BALANCE_REPLACED_ROOT : BalanceStatus::TREE_BALANCED;
		}

		Node* t_root = *root;
		BalanceStatus result = change_to_largest(&(*root)->right, node_to_change);
		if (t_root == (*node_to_change)->left)
		{
			root = &(*node_to_change)->left;
		}

		switch (result)
		{
		case BalanceStatus::TREE_BALANCED:
			return BalanceStatus::TREE_BALANCED;
			break;
		case BalanceStatus::BALANCE_REPLACED_ROOT:
			if (/*(*root)->left != nullptr && */!(*root)->left->black)
			{
				*root = rotate(*root, true);
				(*root)->black = true;
				(*root)->right->black = false;
				return BalanceStatus::TREE_BALANCED;
			}
			else
			{
				Node* tmp = (*root)->left;
				// If left is red
				if ((tmp->left != nullptr && !tmp->left->black))
				{
					// â
					tmp->black = (*root)->black;
					tmp->left->black = (*root)->black = true;
					*root = rotate(*root, true);
					return BalanceStatus::TREE_BALANCED;
				}
				// If right is red
				else if ((tmp->right != nullptr && !tmp->right->black))
				{
					// á
					tmp->black = false;
					tmp->right->black = true;
					(*root)->left = rotate(tmp, false);
					// followed by â
					tmp->black = (*root)->black;
					tmp->left->black = (*root)->black = true;
					*root = rotate(*root, true);
					return BalanceStatus::TREE_BALANCED;
				}
				else
				{
					// à
					tmp->black = false;
					return BalanceStatus::BALANCE_REPLACED_ROOT;
				}
			}
			break;
		default:
			break;
		}
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

	BalanceStatus insert(Node** root, const T& obj)
	{
		if (*root == nullptr)
		{
			*root = new Node(obj);
			return BalanceStatus::CHECK_ROOT;
		}
		BalanceStatus result = insert(&(obj > (*root)->data ? (*root)->right : (*root)->left), obj);

		switch (result)
		{
		case BalanceStatus::CHECK_ROOT:
			if ((*root)->black)
			{
				return BalanceStatus::TREE_BALANCED;
			}
			else
			{
				return BalanceStatus::BALANCE_ROOT;
			}
			break;
		case BalanceStatus::BALANCE_ROOT:
		{
			Node** father;
			Node* uncle;
			bool right_root_subtree = obj > (*root)->data;
			if (right_root_subtree)
			{
				father = &(*root)->right;
				uncle = (*root)->left;
			}
			else
			{
				father = &(*root)->left;
				uncle = (*root)->right;
			}

			if (uncle != nullptr && !uncle->black)
			{
				uncle->black = (*father)->black = true;
				(*root)->black = false;
				return BalanceStatus::CHECK_ROOT;
			}
			else
			{
				(*father)->black = true;
				(*root)->black = false;
				if (right_root_subtree)
				{
					if (obj < (*father)->data)
					{
						*father = rotate(*father, true);
					}
					*root = rotate(*root, false);
				}
				else
				{
					if (obj > (*father)->data)
					{
						*father = rotate(*father, false);
					}
					*root = rotate(*root, true);
				}
				// BIGG ??????????????????????????????????

				return BalanceStatus::TREE_BALANCED;
			}
			break;
		}
		case BalanceStatus::TREE_BALANCED:
			return BalanceStatus::TREE_BALANCED;
			break;
		default:
			throw;
			break;
		}
	}

	void clear_root(Node* root)
	{
		if(root->left != nullptr)
			clear_root(root->left);
		if (root->right != nullptr)
			clear_root(root->right);
		delete root;
	}

	void print_with_root(std::ostream& os, Node* root, int depth = 1, bool left = false) const
	{
		HANDLE console_color;
		console_color = GetStdHandle(
			STD_OUTPUT_HANDLE);
		Node* cur = root;

		if (cur->right != nullptr)
		{
			print_with_root(os, cur->right, depth + 1);
		}
		//os << std::endl
		//	<< std::string(4 * (depth - 1), ' ') << "\x1B[" << (root->black ? "37" : "31") << "m" << (left ? 'L' : 'R') << root->data << "\033[0m\t\t" << std::endl;
		os << std::endl
				<< std::string(4 * (depth - 1), ' ') << (root->black ? "b" : "r") << (left ? 'L' : 'R') << root->data<< std::endl;
		if (cur->left != nullptr)
		{
			print_with_root(os, cur->left, depth + 1, true);
		}
	}

	//BalanceStatus get_replacement(Node** root)
	//{
	//
	//	BalanceStatus result = change_to_largest(root, &node_to_change);
	//
	//	switch (result)
	//	{
	//	case BalanceStatus::TREE_BALANCED:
	//		return BalanceStatus::TREE_BALANCED;
	//		break;
	//	case BalanceStatus::BALANCE_ROOT:
	//		if (/*(*root)->left != nullptr && */!(*root)->left->black)
	//		{
	//			*root = rotate(*root, true);
	//			(*root)->black = true;
	//			(*root)->right->black = false;
	//			return BalanceStatus::TREE_BALANCED;
	//		}
	//		else
	//		{
	//			Node* tmp = (*root)->left;
	//			// If left is red
	//			if ((tmp->left != nullptr && !tmp->left->black))
	//			{
	//				// â
	//				tmp->black = (*root)->black;
	//				tmp->left->black = (*root)->black = true;
	//				*root = rotate(*root, true);
	//				return BalanceStatus::TREE_BALANCED;
	//			}
	//			// If right is red
	//			else if ((tmp->right != nullptr && !tmp->right->black))
	//			{
	//				// á
	//				tmp->black = false;
	//				tmp->right->black = true;
	//				(*root)->left = rotate(tmp, false);
	//				return BalanceStatus::TREE_BALANCED;
	//			}
	//			else
	//			{
	//				// à
	//				tmp->black = false;
	//				return BalanceStatus::BALANCE_ROOT;
	//			}
	//		}
	//		break;
	//	default:
	//		break;
	//	}
	//	/*Node** cur = &replace->left->right;
	//	while ((*cur)->right != nullptr)
	//	{
	//		cur = &(*cur)->right;
	//	}
	//	replace->data = std::move((*cur)->data);
	//	if ((*cur)->left != nullptr)
	//	{
	//		(*cur)->data = std::move((*cur)->left->data);
	//		delete (*cur)->left;
	//		(*cur)->left = nullptr;
	//	}
	//	else
	//	{
	//		delete* cur;
	//		*cur = nullptr;
	//	}*/
	//}

	template<typename U>
	friend std::ostream& operator<<(std::ostream& os, const RBTree<U>& obj);

	Node* root = nullptr;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const RBTree<T>& obj)
{
	obj.print_with_root(os, obj.root);
	return os;
}