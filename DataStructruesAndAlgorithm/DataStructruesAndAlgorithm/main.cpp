#include "BinarySearchTree.h"
#include "HashSep.h"
#include "BinHeap.h"
#include "Sort.h"
#include <iostream>
#include "LeetCode.h"

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
	//for (int i = 0; i < 7;++i)
	//{
	//	std::cout << b[i] << std::endl;
	//}
	int arr2[] = { 4,1,2,7,8,3,2,6,7 };
	SORT::QuickSort(arr2, 0, 8);
	vector<int> m = { 0,4,3,0};
	Solution1 s;
	
	vector<int> in = s.twoSum(m, 0);

	char *a = "pwwkew";
	int cout = lengthOfLongestSubstring(a);

	vector<int> aa1 = { 1,  2 };
	vector<int> aa2 = { 3,4 };
	Solution4 s4;
	double r = s4.findMedianSortedArrays(aa1, aa2);

	Solution5 s5;
	string src5 = "ccc";
	string r5 = s5.longestPalindrome(src5);

	Solution7 s7;
	int ret7 = s7.reverse2(153423646);
	getchar();
}