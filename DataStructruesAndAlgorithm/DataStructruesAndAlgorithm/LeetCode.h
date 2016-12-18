#include <vector>
#include <algorithm>
#include <string>
using namespace std;
/*
1. Two Sum
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution.

Example:
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return[0, 1].
*/

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

/*3. Longest Substring Without Repeating Characters
Given a string, find the length of the longest substring without repeating characters.

Examples:
Given "abcabcbb", the answer is "abc", which the length is 3.
Given "bbbbb", the answer is "b", with the length of 1.
Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.*/

int lengthOfLongestSubstring(char* s) {
	if (strlen(s) == 0)
		return 0;
	bool isAppeared[126];
	for (int i = 0; i < 126; ++i) //�����Խ��
		isAppeared[i] = false;
	char* start = s, *end = s;
	int max = 0, cur = 1;

	while (*start)
	{
		if (((*end) != '\0') && (isAppeared[(*end)] == false))
		{
			isAppeared[(*end)] = true;
			++end;
			++cur;
			if (cur > max)
				max = cur;
		}
		else
		{
			for (int i = 0; i < 126; ++i)
				isAppeared[i] = false;
			++start;
			end = start;
			cur = 1;
		}
	}
	return (--max);
}

class Solution4 {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int m = nums1.size();
		int n = nums2.size();
		vector<int> des;

		vector<int>::iterator it1 = nums1.begin();
		vector<int>::iterator it2 = nums2.begin();

		while (it1 != nums1.end() || it2 != nums2.end())
		{
			double a, b;
			if (it1 == nums1.end())
				a = 999999;
			else
				a = *it1;

			if (it2 == nums2.end())
				b = 999999;
			else
				b = *it2;

			if (a < b)
			{
				des.push_back(a);
				it1++;
			}
			else
			{
				des.push_back(b);
				it2++;
			}
		}

		double desSize = des.size();
		double ret = 0;
		if (desSize == 1)
			return des[0];
		if (des.size() % 2 == 0)
			ret = ((double)des[desSize / 2] + (double)des[desSize / 2 - 1]) / (double)2;
		else
			ret = (double)des[desSize / 2];

		return ret;
	}
};

/*5. Longest Palindromic Substring
Given a string s, find the longest palindromic substring in s.You may assume that the maximum length of s is 1000.

Example:

Input : "babad"

Output : "bab"

Note : "aba" is also a valid answer.
Example :

Input : "cbbd"

Output : "bb"*/
class Solution5 {
public:
	string longestPalindrome(string s) {
		if (s.size() == 1)
		{
			string ret;
			ret.push_back(s[0]);
			return ret;
		}

		string maxPalindromeStr;
		for (int i = 0; i<s.size(); ++i)
		{
			string curPalindromeStr = this->palindrome(s, i);
			if (curPalindromeStr.size()>maxPalindromeStr.size())
				maxPalindromeStr = curPalindromeStr;
		}
		return maxPalindromeStr;
	}

	string palindrome(string s, int i) {
		int oddLeft = i;
		int oddRight = i;
		while (oddLeft > 0 && oddRight < s.size() && s[oddLeft - 1] == s[oddRight + 1])
		{
			--oddLeft;
			++oddRight;
		}

		int evenLeft = i - 1;
		int evenRight = i;
		while (evenLeft >= 0 && evenRight < s.size() && s[evenLeft] == s[evenRight])
		{
			--evenLeft;
			++evenRight;
		}
		++evenLeft;
		--evenRight;

		string palindromeStr;
		if ((oddRight - oddLeft) >= (evenRight - evenLeft))
		{
			for (int k = oddLeft; k <= oddRight; k++)
				palindromeStr.push_back(s[k]);
		}
		else
		{
			for (int k = evenLeft; k <= evenRight; k++)
				palindromeStr.push_back(s[k]);
		}
		return palindromeStr;
	}

};