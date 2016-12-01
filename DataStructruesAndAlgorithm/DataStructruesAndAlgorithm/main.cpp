#include "BinarySearchTree.h"
#include "HashSep.h"
#include "BinHeap.h"
#include "Sort.h"
#include <iostream>

void main()
{
	using namespace DSA;
	using namespace BH;
	//BinarySearchTree<int>* bst = new BinarySearchTree<int>();
	////const int a = 1;
	//for (int i = 0; i < 100; i++)
	//{
	//	bst->insert(i);
	//}
	//bst->inOrder();
	//bool ret = bst->contains(43);
	//for (int i = 50; i < 70; i++)
	//{
	//	bst->remove(i);
	//}
	//bst->preOrder();
	////getchar();

	//HashTable ht = InitializeTable(87);
	//for (int i = 0; i < 87; ++i)
	//{
	//	insert(i + 100, ht);
	//	int b = i;
	//}
	PriorityQueue pq = Initialize(38);
	for (int i = 0; i < 38; ++i)
	{
		BH::Insert(i, pq);
	}
	int p = BH::FindMin(pq);

	int Arr[7] = { 5, 11, 7, 2, 3, 17 };
	int *b = SORT::HeapSort(Arr, 6);
	for (int i = 0; i < 7;++i)
	{
		std::cout << b[i] << std::endl;
	}
	int arr2[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	SORT::MergeSortMe(arr2, 9);
	getchar();
}