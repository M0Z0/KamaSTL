#include "BinarySearchTree.h"

void main()
{
	using namespace DSA;
	BinarySearchTree<int>* bst = new BinarySearchTree<int>();
	//const int a = 1;
	for (int i = 0; i < 100;i++)
	{
		bst->insert(i);
	}
	bst->preOrder();

}