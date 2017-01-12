#include "BinarySearchTree.h"
#include "HashSep.h"
#include "BinHeap.h"
#include "Sort.h"
#include <iostream>
#include "LeetCode.h"
#include "test.h"

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

	Solution8 s8;
	int ret8 = s8.myAtoi("--++12p3");

	Solution9 s9;
	int ret9 = s9.isPalindrome(12);

	Solution12 s12;
	string ret12 = s12.intToRoman(3999);

	vector<string> vec14;
	string str1 = "asdqwe";
	string str2 = "asdd";
	//vec14.push_back(str1);
	//vec14.push_back(str2);
	Solution14 s14;
	string ret14 = s14.longestCommonPrefix(vec14);

	Solution15 s15;
	vector<int> vec15 = { -1, 0, 1, 2, -1, -4 };
	vector<vector<int>> ret15 = s15.threeSum(vec15);

	Solution16 s16;
	vector<int> vec16 = { 0, 2, 1, -3};
	int ret16 = s16.threeSumClosest(vec16, 1);

	Solution19 s19;
	ListNode *head = s19.init();
	ListNode *ret19 = s19.removeNthFromEnd(head, 1);
	//for (; ret19->next != NULL; ret19 = ret19->next)
	//{
	//	std::cout << ret19->val << std::endl;
	//}

	Solution20 s20;
	string str20 = "[[";
	int ret20 = s20.isValid(str20);

	Solution24 s24;
	ListNode *head24 = s24.init();
	ListNode *ret24 = s24.swapPairs(head24);
	for (; ret24->next != NULL; ret24 = ret24->next)
	{
		std::cout << ret24->val << std::endl;
	}

	vector<int> v26 = {1,1,2};
	Solution26 s26;
	int r26 = s26.removeDuplicates(v26);

	vector<int> v33 = {3,4,5,6,7,8,1,2};
	Solution33 s33;
	int r33 = s33.search(v33, 1);

	vector<int> v34 = {};
	Solution34 s34;
	vector<int> r34 = s34.searchRange(v34, 0);

	Solution39 s39;
	vector<int> v39 = {2,3,6,7};
	vector<vector<int>> r39 = s39.combinationSum(v39, 7);

	Solution43 s43;
	string r43 = s43.multiply("87", "3245");

	Solution46 s46;
	vector<int> v46 = { 1,2,3 };
	vector<vector<int>> r46 = s46.permute(v46);

	Solution49 s49;
	vector<string> v49 = { "eat", "tea", "tan", "ate", "nat", "bat" };
	//vector<string> v49 = { "" };
	vector<vector<string>> r49 = s49.groupAnagrams(v49);

	Solution50 s50;
	double r50 = s50.pow(2, 4);
	getchar();
}