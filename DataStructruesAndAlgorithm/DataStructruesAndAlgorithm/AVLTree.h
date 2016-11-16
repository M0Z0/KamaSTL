#ifndef _AVL_TREE_
#define _AVL_TREE_

#define max(a, b) (((a) > (b)) ? (a) : (b))

namespace DSA{

	template<class type>
	class AVLTree{
	public:
		struct AvlNode;
		AVLTree() : root(nullptr) {}
	private:
		struct AvlNode
		{
			type element;
			AvlNode *left;
			AvlNode *right;
			int height;

			AvlNode(const type& ele, AvlNode *lt, AvlNode *rt, int h = 0) :
				element(ele), left(lt), right(rt), height(h) {}
		};

		AVLTree* root;
	public:
		inline int height(AvlNode* t) const
		{
			return t == nullptr ? -1 : t->height;
		}

		inline void insert(const type &ele, AvlNode *&t)
		{
			if (t == nullptr)
			{
				t = new AvlNode(ele, nullptr, nullptr);
			}
			else if (ele < t->element)
			{
				insert(ele, t->left);
				if (height(t->left) - height(t->right) == 2)
				{
					if (ele < t->left->element)
						singleRotateLeftChild(t);
					else
						doubleRotateLeftChild(t);
				}
			}
			else if (ele > t->element)
			{
				insert(ele, t->right);
				if (height(t->left) - height(t->right) == 2)
				{
					if (ele > t->right->element)
						singleRotateRightChild(t);
					else
						doubleRotateRightChild(t);
				}
			}
			else
				;
			t->height = max(height(t->left), height(t->right)) + 1;
		}

		inline void singleRotateLeftChild(AvlNode *& k2)
		{
			AvlNode *k1 = k2->left;
			k2->left = k1->right;
			k1->right = k2;
			k2->height = max(height(k2->left), height(k2->right)) + 1;
			k1->height = max(height(k1->left), k2->height) + 1;
			k2 = k1; //传出k1
		}

		inline void singleRotateRightChild(AvlNode *& k1)
		{
			AvlNode *k2 = k1->right;
			k1->right = k2->left;
			k2->left = k1;
			k1->height = max(height(k1->left), height(k1->right)) + 1;
			k2->height = max(k1->height, k2->right) + 1;
			k1 = k2; //传出k2
		}

		inline void doubleRotateLeftChild(AvlNode *& k3)
		{
			this->singleRotateRightChild(k3->left);
			this->singleRotateLeftChild(k3);
		}

		inline void doubleRotateRightChild(AvlNode *& k3)
		{
			this->singleRotateLeftChild(k3->right);
			this->singleRotateRightChild(k3);
		}
	};//end of class
}

#endif