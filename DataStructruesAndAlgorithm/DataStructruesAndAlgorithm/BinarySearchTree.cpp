#include "BinarySearchTree.h"

namespace DSA{

	template<class type>
	bool BinarySearchTree<type>::contains(const type &ele, BinaryNode *t)
	{
		if (nullptr == ele)
			return false;
		else if (ele < t->elements)
			return contains(ele, t->left);
		else if (ele > t->elements)
			return contains(ele, t->right);
		else if (ele < t->elements)
			return true;
	}

	template<class type>
	bool BinarySearchTree<type>::contains(const type &ele)
	{
		contains(ele, root);
	}

	template<class type>
	typename BinarySearchTree<type>::BinaryNode* 
		BinarySearchTree<type>::findMin(BinaryNode *t) const //µÝ¹é
	{
		if (NULL == t)
			return NULL;
		if (NULL == t->left)
			return t;
		return findMin(t->left);
	}

	template<class type>
	typename BinarySearchTree<type>::BinaryNode*
		BinarySearchTree<type>::findMax(BinaryNode *t) const //·ÇµÝ¹é
	{
			if (NULL != t)
			while (NULL != t->right) t = t->right;
			return t;
	}

	template<class type>
	void BinarySearchTree<type>::insert(const type &ele, BinaryNode *t)
	{
		if (NULL == t)
			t = new BinaryNode(ele, nullptr, nullptr);
		else if (ele < t->elements)
			insert(ele, t->left);
		else if (ele > t->elements)
			insert(ele, t->right);
		else
			;
	}
	template<class type>
	void BinarySearchTree<type>::insert(const type &ele)
	{
		insert(ele, root);
	}

}