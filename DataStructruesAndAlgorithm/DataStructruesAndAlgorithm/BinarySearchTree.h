#ifndef _BINARY_SEARCH_TREE_
#define _BINARY_SEARCH_TREE_

namespace DSA{

	template<class type>
	class BinarySearchTree{
	public:
		struct BinaryNode;
		BinarySearchTree() : root(nullptr) {}
		BinarySearchTree(const BinarySearchTree& rhs);
		~BinarySearchTree();
		const BinarySearchTree& operator=(const BinarySearchTree& rhs);

		bool contains(const type &ele);
		BinaryNode* findMin(BinaryNode *t) const;
		BinaryNode* findMax(BinaryNode *t) const;
		void insert(const type &ele);
		void remove(const type &ele);
		void makeEmpty(BinaryNode *t);
		void preOrder();

	private:
		struct BinaryNode 
		{
			type elements;
			BinaryNode *left;
			BinaryNode *right;

			BinaryNode(const type& ele, BinaryNode *lt, BinaryNode *rt) :
				elements(ele), left(lt), right(rt) {}
		};
		BinaryNode *root;

		bool contains(const type &ele, BinaryNode *t);
		void insert(const type &ele, BinaryNode *&t);
		void remove(const type &ele, BinaryNode *t);
		BinaryNode* clone(BinaryNode* t) const;
		void preOrder(BinaryNode *&t) const;
	};//End of class
}

#include "BinarySearchTree.impl.h"
#endif