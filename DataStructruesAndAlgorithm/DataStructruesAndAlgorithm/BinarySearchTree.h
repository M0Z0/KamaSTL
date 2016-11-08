#ifndef _BINARY_SEARCH_TREE_
#define _BINARY_SEARCH_TREE_

namespace DSA{

	template<class type>
	class BinarySearchTree{
	public:
		struct BinaryNode;
		BinarySearchTree();
		BinarySearchTree(const BinarySearchTree& rhs);
		~BinarySearchTree();

		bool contains(const type &ele);
		BinaryNode* findMin(BinaryNode *t) const;
		BinaryNode* findMax(BinaryNode *t) const;
	private:
		struct BinaryNode 
		{
			type elements;
			BinaryNode *left;
			BinaryNode *right;
			BinaryNode(const BinaryNode& ele, BinaryNode *lt, BinaryNode *rt) :
				elements(ele), lt(left), right(rt) {}
		};
		BinaryNode *root;

		bool contains(const type &ele, BinaryNode *t);
	};//End of class
}

#endif