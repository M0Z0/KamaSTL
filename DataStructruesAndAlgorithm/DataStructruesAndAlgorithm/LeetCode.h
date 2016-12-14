/*
1. Two Sum
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution.

Example:
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return[0, 1].
*/

#include <vector>
#include <algorithm>
using namespace std;
class Solution1 {
public:
	vector<int> twoSum(vector<int>& nums, int target) 
	{
		vector<int> numCopy = nums;
		std::sort(numCopy.begin(), numCopy.end());
		int i = 0;
		int len = nums.size();
		int j = len - 1;

		vector<int> ret;
		while (i<j)
		{
			int sum = numCopy[i] + numCopy[j];
			if (sum==target)
			{
				for (int k = 0; k < len; ++k)
				{
					if (numCopy[i] == nums[k])
					{
						ret.push_back(k);
						break;
					}
				}
				for (int h = len-1; h > -1; --h)
				{
					if (numCopy[j] == nums[h])
					{
						ret.push_back(h);
						break;
					}
				}
				break;
			}
			else if (sum>target)
			{
				j--;
			}
			else if (sum<target)
			{
				i++;
			}
		}
		return ret;
	}
};

/*2. Add Two Numbers   
Add to List QuestionEditorial Solution  My Submissions
You are given two linked lists representing two non - negative numbers.The digits are stored in reverse order and each of their nodes contain a single digit.Add the two numbers and return it as a linked list.
Input : (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output : 7 -> 0 -> 8
*/
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution2 {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* tail = new ListNode(0);
		int carry = 0;
		ListNode* ptr = tail;

		while (l1 != NULL || l2 != NULL)
		{
			int l1Digit = 0;
			if (l1 != NULL)
			{
				l1Digit = l1->val;
				l1 = l1->next;
			}


			int l2Digit = 0;
			if (l2 != NULL)
			{
				l2Digit = l2->val;
				l2 = l2->next;
			}


			int sum = l1Digit + l2Digit + carry;
			int des = 0;
			if (sum >= 10)
			{
				carry = 1;
				des = sum - 10;
			}
			else
			{
				carry = 0;
				des = sum;
			}
			ptr->next = new ListNode(des);
			ptr = ptr->next;
		}

		if (carry == 1)
			ptr->next = new ListNode(1);

		return tail->next;
	}
};