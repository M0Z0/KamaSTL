#include "BinarySearchTree.h"
#include <iostream>

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
		BinarySearchTree<type>::findMin(BinaryNode *t) const //递归
	{
			if (NULL == t)
				return NULL;
			if (NULL == t->left)
				return t;
			return findMin(t->left);
		}

	template<class type>
	typename BinarySearchTree<type>::BinaryNode*
		BinarySearchTree<type>::findMax(BinaryNode *t) const //非递归
	{
			if (nullptr != t)
			while (nullptr != t->right) t = t->right;
			return t;
		}

	template<class type>
	void BinarySearchTree<type>::insert(const type &ele, BinaryNode *&t)
	{
		if (nullptr == t)
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


	template<class type>
	void BinarySearchTree<type>::remove(const type &ele, BinaryNode *t)
	{
		if (NULL == t)
			return;
		else if (ele < t->elements)
			remove(ele, t->left);
		else if (ele > t->elements)
			remove(ele, t->right);
		else if (t->left != NULL &&t->right != NULL) //有两个儿子结点
		{
			BinaryNode *miniNode = findMin(t->right);
			t->elements = miniNode->elements;
			remove(t->elements, t->right);
		}
		else
		{
			BinaryNode *oldNode = t;
			t = (t->left != NULL) ? t->left : t->right;
			delete oldNode;
		}
	}

	template<class type>
	void BinarySearchTree<type>::remove(const type &ele)
	{
		remove(ele, root);
	}

	template<class type>
	void BinarySearchTree<type>::makeEmpty(BinaryNode* t)
	{
		if (NULL != t)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = NULL;
	}

	template<class type>
	BinarySearchTree<type>::~BinarySearchTree()
	{
		makeEmpty(root);
	}

	template<class type>
	typename BinarySearchTree<type>::BinaryNode*
		BinarySearchTree<type>::clone(BinaryNode* t) const
	{
			if (NULL == t)
				return NULL;

			return new BinarySearchTree(t->elements, clone(t->left), clone(t->right));
		}

	template<class type>
	const BinarySearchTree<type>& BinarySearchTree<type>::operator=(const BinarySearchTree& rhs)
	{
		if (*this != rhs)
		{
			makeEmpty(root);
			root = clone(rhs.root);
		}
		return *this;
	}

	template<class type>
	void BinarySearchTree<type>::preOrder(BinaryNode *&t) const
	{
		if (t)
		{
			std::cout << t->elements << " ";
			preOrder(t->left);
			preOrder(t->right);
		}
	}

	template<class type>
	void BinarySearchTree<type>::preOrder()
	{
		this->preOrder(root);
	}

}