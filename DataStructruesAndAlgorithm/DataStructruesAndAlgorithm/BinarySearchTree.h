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
		void insert(const type &ele);
		void remove(const type &ele);
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
		void insert(const type &ele, BinaryNode *t);
		void remove(const type &ele, BinaryNode *t);
	};//End of class
}

#endif