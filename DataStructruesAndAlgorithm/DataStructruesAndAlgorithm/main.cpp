#include "BinarySearchTree.h"

void main()
{
	using namespace DSA;
	BinarySearchTree<int>* bst = new BinarySearchTree<int>();
	//const int a = 1;
	for (int i = 0; i < 100; i++)
	{
		bst->insert(i);
	}
	bst->inOrder();
	bool ret = bst->contains(43);
	for (int i = 50; i < 70; i++)
	{
		bst->remove(i);
	}
	bst->preOrder();
	getchar();

}