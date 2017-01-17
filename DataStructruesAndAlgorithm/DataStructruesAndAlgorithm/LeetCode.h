#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <map>
#include <stack>
#include <queue> 
#include <map>
#include <unordered_map>
using namespace std;
/*
1. Two Sum
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution.

Example:
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return[0, 1].

先排序，然后两个指针分头在头尾，指向元素和大于target就尾指针减一，否则头指针加一
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
		while (i < j)
		{
			int sum = numCopy[i] + numCopy[j];
			if (sum == target)
			{
				for (int k = 0; k < len; ++k)
				{
					if (numCopy[i] == nums[k])
					{
						ret.push_back(k);
						break;
					}
				}
				for (int h = len - 1; h > -1; --h)
				{
					if (numCopy[j] == nums[h])
					{
						ret.push_back(h);
						break;
					}
				}
				break;
			}
			else if (sum > target)
			{
				j--;
			}
			else if (sum < target)
			{
				i++;
			}
		}
		return ret;
	}
};

/*2. Add Two Numbers
You are given two linked lists representing two non - negative numbers.The digits are stored in reverse order and each of their nodes contain a single digit.Add the two numbers and return it as a linked list.
Input : (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output : 7 -> 0 -> 8
注意进位
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
Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
思路：头尾指针，没出现过就尾指针加一，否则头指针加一，重置尾指针*/

int lengthOfLongestSubstring(char* s) {
	if (strlen(s) == 0)
		return 0;
	bool isAppeared[126];
	for (int i = 0; i < 126; ++i) //数组别越界
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

/*4. Median of Two Sorted Arrays
There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:
nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:
nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5
思路：
先归并排序，然后算出中间值*/
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

/*6. ZigZag Conversion

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line : "PAHNAPLSIIGYIR"
Write the code that will take a string and make this conversion given a number of rows :

string convert(string text, int nRows);
convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".*/

class Solution6 {
public:
	string convert(string s, int numRows) {
		if (numRows <= 1 || s.length() == 0)
			return s;

		string res = "";
		int len = s.length();
		for (int i = 0; i < len && i < numRows; ++i)
		{
			int indx = i;
			res += s[indx];

			for (int k = 1; indx < len; ++k)
			{
				//第一行或最后一行，使用公式1：  
				if (i == 0 || i == numRows - 1)
				{
					indx += 2 * numRows - 2;
				}
				//中间行，判断奇偶，使用公式2或3  
				else
				{
					if (k & 0x1)  //奇数位  
						indx += 2 * (numRows - 1 - i);
					else indx += 2 * i;
				}

				//判断indx合法性  
				if (indx < len)
				{
					res += s[indx];
				}
			}
		}
		return res;
	}
};
/*7. Reverse Integer
Reverse digits of an integer.
Example1: x = 123, return 321
Example2 : x = -123, return -321*/
class Solution7 {
public:
	int reverse1(int x) {
		if (x > -10 && x < 10)
			return x;
		int y = x;
		if (x<0)
		{
			x *= -1;
		}
		list<int> li;
		int tmp = 1;
		int count = 0;
		for (;;) {
			int bit = x%10;
			if (x != 0) {
				li.push_back(bit);
				tmp *= 10;
				x /= 10;
			}
			else{
				break;
			}
		}
		int digit = 0;
		tmp /= 10;

		bool noAdd = true;
		list<int>::iterator it = li.begin();
		for (; it != li.end(); ++it)
		{
			int t = *it;
			if (t == 0 && noAdd)
			{
				tmp /= 10;
				continue;
			}
			else
			{
				noAdd = false;
				digit = digit + (t*tmp);
				tmp /= 10;
			}
		}
		if (y < 0)
			digit *= -1;
		return digit;
	}
	int reverse2(int x) {
		// Note: The Solution object is instantiated only once and is reused by each test case.  
		int result = 0;

		int flag = 0;
		if (x < 0)
		{
			flag = 1;
			x = -x;
		}

		int lastDigit = 0;
		while (x > 0)
		{
			lastDigit = x - x / 10 * 10;
			result = result * 10 + lastDigit;
			x /= 10;
		}

		if (flag == 1)
		{
			result = -result;
		}

		return result;
	}
};

/*8. String to Integer(atoi)
Implement atoi to convert a string to an integer.
Hint: Carefully consider all possible input cases.If you want a challenge, please do not see below and ask yourself what are the possible input cases.
  Notes : It is intended for this problem to be specified vaguely(ie, no given input specs).You are responsible to gather all the input requirements up front.*/
class Solution8 {
public:
	int myAtoi(string str) {
		int len = str.length();
		if (len == 0)
			return 0;
		long long tmp = 0;
		bool bNofirst = false;
		bool bNegative = false;
		for (int i = 0; i != len; ++i) {
			if (str[i] >= '0' && str[i] <= '9') {
				tmp = tmp * 10 + str[i] % 48;
				bNofirst = true;
			}
			else if (str[i] == '-' && bNofirst == false) //数字前的合法字符是负号
				bNegative = true;
			else if (str[i] == '+' && bNofirst == false) //数字前的合法字符是正数
				bNegative = false;
			else if ((str[i] == '-' && bNofirst == true) ||
				(str[i] == '+' && bNofirst == true))
				break;
			else if (str[i] == '\0')
				;
			else
				return 0;
		}
		if (bNegative)
			tmp = -tmp;
		if (tmp>INT_MAX)
			return INT_MAX;	
		else if (tmp<INT_MIN)
		    return INT_MIN;
		else
			return (int)tmp;
	}
};

/*9. Palindrome Number
Determine whether an integer is a palindrome.Do this without extra space.*/
class Solution9 {
public:
	bool isPalindrome(int x) {
		if (x < 0)
			return false;
		else if (x >= 0 && x<10)
			return true;
		int vec[20] = { 0 };
		int count = 0;
		for (;;) {
			int remainder = x % 10;
			x /= 10;
			if (x == 0 && remainder == 0)
				break;
			else
				vec[count++] = remainder;
		}

		int ret = true;
		int times = count / 2;
		int c = --count;
		for (int i = 0; times != 0; --times, ++i) {
			if (vec[i] != vec[c--]) {
				ret = false;
				break;
			}
		}
		return ret;
	}

	bool isPalindromeC(int x) {
		if (x < 0) return false;
		int y = 1;
		while (x / y >= 10)
			y *= 10;

		while (x) {
			if (x / y != x % 10) return false;
			x = (x % y) / 10;
			y /= 100;
		}
		return true;
	}
};

/*11. Container With Most Water
Given n non - negative integers a1, a2, ..., an, where each represents a point at coordinate(i, ai).n vertical lines are drawn such that the two endpoints of line i is at(i, ai) and(i, 0).Find two lines, which together with x - axis forms a container, such that the container contains the most water.
Note: You may not slant the container and n is at least 2.*/
class Solution11 {
public:
	int maxArea(vector<int>& height) {
		int n = height.size();
		int maxArea = 0;
		int i = 0;
		int j = n - 1;
		while (i<j)
		{
			int temp = (j - i)*(height[i]>height[j] ? height[j] : height[i]);
			if (height[i] < height[j])
			{
				i++;
			}
			else
			{
				j--;
			}
			if (maxArea < temp)
			{
				maxArea = temp;
			}
		}
		return maxArea;
	}
};

/*12. Integer to Roman
Given an integer, convert it to a roman numeral.
Input is guaranteed to be within the range from 1 to 3999.
罗马数字规则：
1， 罗马数字共有7个，即I（1）、V（5）、X（10）、L（50）、C（100）、D（500）和M（1000）。
罗马数字中没有“0”。
2， 重复次数：一个罗马数字最多重复3次。
3， 右加左减：
在较大的罗马数字的右边记上较小的罗马数字，表示大数字加小数字。
在较大的罗马数字的左边记上较小的罗马数字，表示大数字减小数字。
4， 左减的数字有限制，仅限于I、X、C，且放在大数的左边只能用一个。
(*) V 和 X 左边的小数字只能用Ⅰ。
(*) L 和 C 左边的小数字只能用X。
(*) D 和 M 左 边的小数字只能用C。*/
class Solution12 {
public:
	struct node{
		int key;
		string szRoman;
		node(int k, string s) :key(k), szRoman(s){}
	};

	string intToRoman(int num) {
		vector<node> dct;
		dct.push_back(node(1000, "M"));
		dct.push_back(node(900, "CM"));
		dct.push_back(node(500, "D"));
		dct.push_back(node(400, "CD"));
		dct.push_back(node(100, "C"));
		dct.push_back(node(90, "XC"));
		dct.push_back(node(50, "L"));
		dct.push_back(node(40, "XL"));
		dct.push_back(node(10, "X"));
		dct.push_back(node(9, "IX"));
		dct.push_back(node(5, "V"));
		dct.push_back(node(4, "IV"));
		dct.push_back(node(1, "I"));

		string res;
		int i = 0;
		while (num > 0)
		{
			if (num / dct[i].key == 0)
			{
				i += 1;
				continue;
			}

			for (int j = 0; j < num / dct[i].key; ++j)
				res.append(dct[i].szRoman);

			num %= dct[i].key;
		}
		return res;
	}
};


/*13. Roman to Integer
Given a roman numeral, convert it to an integer.
Input is guaranteed to be within the range from 1 to 3999.*/
class Solution13 {
public:
	int romanToInt(string s) {
		map<char, int> dct;
		dct['I'] = 1, dct['i'] = 1;
		dct['V'] = 5, dct['v'] = 5;
		dct['X'] = 10, dct['x'] = 10;
		dct['L'] = 50, dct['l'] = 50;
		dct['C'] = 100, dct['c'] = 100;
		dct['D'] = 500, dct['d'] = 500;
		dct['M'] = 1000, dct['m'] = 1000;

		int sum = 0;
		int j = 0;
		for (int i = 0; i < s.size(); ++i) {
			j = i + 1;
			if (j<s.size() && dct[s[j]]>dct[s[i]]) {
				sum += (dct[s[j]] - dct[s[i]]);
				i = j;
			}
			else{
				sum += dct[s[i]];
			}
		}
		return sum;
	}
};

/*14. Longest Common Prefix
Write a function to find the longest common prefix string amongst an array of strings.*/
class Solution14 {
public:
	string longestCommonPrefix(vector<string>& strs) {
		int size = strs.size();
		if (size == 0)
			return "";

		string longPrefix = strs[0];
		for (int i = 1; i < size; ++i) {
			if (longPrefix.length() == 0 || strs[i].length() == 0)
				return "";
			int len = longPrefix.length() < strs[i].length() ? longPrefix.length() : strs[i].length();
			int j = 0;
			for (; j < len; ++j) {
				if (longPrefix[j] != strs[i][j])
					break;
			}
			longPrefix = longPrefix.substr(0, j);
		}
		return longPrefix;
	}
};

class Solution15 {
public:
	vector<vector<int> >* v;
	vector<vector<int>> threeSumT(vector<int>& nums) {
		v = new vector<vector<int>>();
		if (nums.size() < 3)
		{
			return *v;
		}

		sort(nums.begin(), nums.end());

		for (int i = 0; i < nums.size() - 2; i++)
		{
			if (i > 0 && nums[i] == nums[i - 1])
			{
				continue;
			}
			for (int j = i + 1; j < nums.size() - 1; j++)
			{
				if (j > i + 1 && nums[j] == nums[j - 1])
				{
					continue;
				}
				int left = j + 1;
				int right = nums.size() - 1;
				while (left <= right)
				{
					int mid = left + ((right - left) >> 1);
					if (nums[i] + nums[j] + nums[mid] == 0)
					{
						vector<int> tmp;
						tmp.push_back(nums[i]);
						tmp.push_back(nums[j]);
						tmp.push_back(nums[mid]);

						v->push_back(tmp);
						break;
					}
					else if (nums[i] + nums[j] + nums[mid] > 0)
					{
						right = mid - 1;
					}
					else
					{
						left = mid + 1;
					}
				}
			}
		}

		return *v;
	}

	vector<vector<int>> threeSum(vector<int>& nums) {
		std::sort(nums.begin(), nums.end());
		vector<vector<int>> ret;
		vector<int> onceResult;
		for (int i = 0; i < nums.size(); ++i) {
			int j = i + 1;
			int k = nums.size() - 1;
			int target = 0 - nums[i];
			while (j < k) {
				if (nums[j] + nums[k] == target) {
					onceResult.clear();
					onceResult.push_back(nums[i]);
					onceResult.push_back(nums[j]);
					onceResult.push_back(nums[k]);

					/*bool isRepeat = false;
					for(int i=0; i<ret.size();++i)
					if(onceResult == ret[i])
					isRepeat = true;

					if(!isRepeat)*/
					ret.push_back(onceResult);
					++j;
					--k;
					continue;
				}
				else if (nums[j] + nums[k] < target) {
					++j;
				}
				else if (nums[j] + nums[k] > target) {
					--k;
				}
			}
		}
		return ret;
	}
};

class Solution16 { //和sum2类似
public:
	int threeSumClosest(vector<int>& nums, int target) {
		std::sort(nums.begin(), nums.end());
		int min = 65535;
		vector<int> onceResult;
		for (int i = 0; i < nums.size(); ++i) {
			int j = i + 1;
			int k = nums.size() - 1;
			while (j < k) {
				int tmp = 0;
				if (target >(nums[i] + nums[j] + nums[k]))
					tmp = target - (nums[i] + nums[j] + nums[k]);
				else
					tmp = (nums[i] + nums[j] + nums[k]) - target;
				if (tmp < min) {
					min = tmp;
					onceResult.clear();
					onceResult.push_back(nums[i]);
					onceResult.push_back(nums[j]);
					onceResult.push_back(nums[k]);
				}
				if (nums[i] + nums[j] + nums[k] < target) {
					++j;
				}
				else {
					--k;
				}
			}
		}
		return onceResult[0] + onceResult[1] + onceResult[2];
	}
};

/*19. Remove Nth Node From End of List
Given a linked list, remove the nth node from the end of list and return its head.

For example,

Given linked list : 1->2->3->4->5, and n = 2.

After removing the second node from the end, the linked list becomes 1->2->3->5.*/
class Solution19 {
public:
	//typedef struct ListNode ListNode;
	ListNode* init() {
		
		ListNode* p = new ListNode(1);
		//ListNode* q = p;
		//for (int i = 2; i < 6; ++i)
		//{
		//	p->next = new ListNode(i);
		//	p = p->next;
		//}
		//return q;
		return p;
	}
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode* p = head;
		ListNode* q = head;
		int nodeCount = 1;
		for (; p->next != NULL; ++nodeCount, p = p->next) {}
		p = q; //重新把指针指到头
		if (n <= nodeCount) {
			int currentNode = 0;
			if (p->next == NULL)
				return NULL;
			while (p->next != NULL) {
				if (nodeCount - n == 0) {
					head = p->next;
					delete p;
					return head;
				}
				if (currentNode + 1 == (nodeCount - n) && (nodeCount - n) != 0) {
					q = p->next;
					p->next = q->next;
					delete q;
					q = NULL;
					break;
				}
				else{
					p = p->next;
					q = p;
					++currentNode;
				}
			}
		}
		else{
			return NULL;
		}
		return head;
	}
};

/*20. Valid Parentheses
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.*/
class Solution20 {
public:
	bool isValid(string s) {
		stack<char> parStack;
		int length = s.size();
		if (length == 1)
			return false;
		for (int i = 0; i < length; ++i) {
			char c = s[i];
			switch (c) {
			case '(':
			case '{':
			case '[':
				parStack.push(c);
				break;
			case ')':
				if (parStack.empty())
					return false;
				else{
					if (parStack.top() == '('){
						parStack.pop();
						break;
					}
					else
						return false;
				}
			case '}':
				if (parStack.empty())
					return false;
				else{
					if (parStack.top() == '{'){
						parStack.pop();
						break;
					}
					else
						return false;
				}
			case ']':
				if (parStack.empty())
					return false;
				else{
					if (parStack.top() == '['){
						parStack.pop();
						break;
					}
					else
						return false;
				}
			default:
				break;
			}
		}
		return parStack.empty(); //此处应判断是否为空
	}
};

/*21. Merge Two Sorted Lists
Merge two sorted linked lists and return it as a new list.The new list should be made by splicing together the nodes of the first two lists.*/
class Solution21 {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) { //l3指向每次一比较的较小结点，和归并排序类似
		ListNode* l3 = new ListNode(-1); //该结点临时的，第二个结点才是目标list头
		ListNode* head = l3;
		while (l1 && l2) {
			if (l1->val < l2->val) {
				l3->next = l1;
				l1 = l1->next;
			}
			else{
				l3->next = l2;
				l2 = l2->next;
			}
			l3 = l3->next;
			l3->next = NULL;
		}

		l3->next = l1 ? l1 : l2;
		ListNode* tmp = head;
		head = head->next;
		delete tmp;
		return head;
	}
};

/*23. Merge k Sorted Lists
Merge k sorted linked lists and return it as one sorted list.Analyze and describe its complexity.
将每个list的最小节点放入一个priority queue (min heap)中。之后每从queue中取出一个节点，则将该节点在其list中的下一个节点插入，以此类推直到全部节点都经过priority queue。由于priority queue的大小为始终为k，而每次插入的复杂度是log k，一共插入过nk个节点。时间复杂度为O(nk logk)，空间复杂度为O(k)。
注意C++的STL中的priority queue默认是max heap，定义一个新的比较函数。*/
class Solution23 {
public:
	struct cmp{
		bool operator()(ListNode* l1, ListNode* l2) {
			return (l1->val) > (l2->val);
		}
	};
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		priority_queue<ListNode*, vector<ListNode*>, cmp> pq;
		ListNode *dummy = new ListNode(-1);
		ListNode *tail = dummy;
		for (int i = 0; i < lists.size(); ++i) {
			if (lists[i])
				pq.push(lists[i]);
		}

		while (!pq.empty()) {
			dummy->next = pq.top();
			pq.pop();
			dummy = dummy->next;
			if (dummy->next)
				pq.push(dummy->next);
		}
		ListNode *tmp = tail;
		delete tmp;
		tail = tail->next;
		return tail;
	}
};

/*24. Swap Nodes in Pairs
Given a linked list, swap every two adjacent nodes and return its head.
For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.
Your algorithm should use only constant space.You may not modify the values in the list, only nodes itself can be changed.*/
class Solution24 {
public:
	ListNode* init() {

		ListNode* p = new ListNode(1);
		ListNode* q = p;
		for (int i = 2; i < 4; ++i)
		{
			p->next = new ListNode(i);
			p = p->next;
		}
		return q;
		return p;
	}
	void swapNode(int *a, int *b) {
		int tmp = *a;
		*a = *b;
		*b = tmp;
	}
	ListNode* swapPairs(ListNode* head) {
		ListNode* p = head;
		ListNode* p1 = head;
		ListNode* p2 = NULL;
		if (!p1)
			return NULL;
		if (p1->next == NULL)
			return p;
		else
			p2 = p1->next;

		while (p1 && p2) {
			swapNode(&p1->val, &p2->val);
			p1 = p2->next;
			p2 = p1->next;
		}
		return p;
	}
};

class Solution26 {
public:
	int removeDuplicates(vector<int>& nums) {
		int j = 0;
		for (int i = 0; i < nums.size();) {
			j = i + 1;
			if (j < nums.size()) {
				if (nums[i] == nums[j]) {
					nums.erase(nums.begin() + j);
				}
				else{
					++i;
				}
			}
			else{
				break;
			}
		}
		return nums.size();
	}
};


/*直观解法是扫描数组，当遇到value时，将value右边所有元素向左移一格，直接到扫完所有数字。但这种解法在移动操作上的消耗是很大的，最差情况时间复杂度为O(n ^ 2)。

由于数组元素顺序不需要维持，可以采取当遇到value时，用顺组尾部元素来填充。同样是双指针的技巧：left指针扫描数组，right指针表示当前数组的尾端。
(1) A[left] = value时，A[left] = A[right], right--，但不能left++，因为也可能A[right] = value
(2) A[left] != value时，left++*/
class Solution27 {
public:
	int removeElement(int* nums, int numsSize, int val) {
		int left = 0, right = numsSize - 1;
		while (left <= right) {
			if (nums[left] == val)
				nums[left] = nums[right--];
			else
				left++;
		}
		return right + 1;
	}
};

/*
28. Implement strStr()
Implement strStr().
Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.*/
class Solution28 {
public:
	int strStr(char* haystack, char* needle) {
		if (!*needle) return 0;
		if (!*haystack) return -1;
		int m = strlen(haystack), n = strlen(needle);

		for (int i = 0; i <= m - n; i++) { //注意此处没有必要全部遍历
			for (int j = 0; j <= n; j++) {
				char *p1 = haystack + i + j;
				char *p2 = needle + j;
				if (!*p2) return i;
				if (*p1 != *p2) break;
			}
		}
		return -1;
	}
};

/*You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.
30. Substring with Concatenation of All Words
For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).
思路：

和strStr那题的双指针解法类似。关键在于如何判断以任意i起始的S的substring是否整个L的concatenation。这里显然要用到hash table。由于L中可能存在重复的word，所以hash table的key = word，val = count of the word。

在建立好L的hash table后，对每个S[i]进行检查。这里的一个技巧建立一个新的hash table记录已经找到的word。因为L的hash table需要反复利用，不能被修改，并且如果以hash table作为参数进行值传递的化，时间空间消耗都很大。
*/
class Solution30 {
public:
	vector<int> findSubstring(string s, vector<string>& words) {
		vector<int> allPos;
		if (words.empty())
			return allPos;
		int totalWords = words.size();
		int wordSize = words[0].size();
		int totalLen = totalWords * wordSize;
		if (s.size() < totalLen)
			return allPos;

		unordered_map<string, int> wordCount;
		for (int i = 0; i < totalWords; ++i)
			wordCount[words[i]]++;

		for (int i = 0; i <= s.size() - totalLen; i++) {
			if (checkSubstring(s, i, wordCount, wordSize, totalWords))
				allPos.push_back(i);
		}
		return allPos;
	}

	bool checkSubstring(string S, int start, unordered_map<string, int> &wordCount, int wordSize, int totalWords) {
		if (S.size() - start + 1 < wordSize*totalWords) return false;
		unordered_map<string, int> wordFound;

		for (int i = 0; i<totalWords; ++i) {
			string curStr = S.substr(start + i*wordSize, wordSize);
			if (wordCount.count(curStr) == 0) return false;
			wordFound[curStr]++;
			if (wordFound[curStr] > wordCount[curStr]) return false;
		}
		return true;
	}
};

/*32. Longest Valid Parentheses
Given a string containing just the characters '(' and ')', find the length of the longest valid(well - formed) parentheses substring.
For "(()", the longest valid parentheses substring is "()", which has length = 2.
Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.*/
class Solution32 {
public:
	int longestValidParentheses(string s) {
		stack<pair<int, int>> stk;   // first: index, second: 0:'(', 1:')'
		int maxLen = 0, curLen = 0;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '(')   // left parenthesis
				stk.push(make_pair(i, 0)); //注意make_pair的使用
			else {          // right parenthesis
				if (stk.empty() || stk.top().second == 1)
					stk.push(make_pair(i, 1));
				else {
					stk.pop();
					if (stk.empty())
						curLen = i + 1;
					else
						curLen = i - stk.top().first;
					maxLen = max(maxLen, curLen);
				}
			}
		}
		return maxLen;
	}
};

/*33. Search in Rotated Sorted Array
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
You are given a target value to search.If found in the array return its index, otherwise return -1.
You may assume no duplicate exists in the array.*/
class Solution33 {
public:
	int search(vector<int>& nums, int target) {
		int start = 0, end = nums.size() - 1;
		while (start <= end) {
			int mid = start + (end - start) / 2;
			if (nums[mid] == target) return mid;

			if (nums[mid]<nums[end]) { // right half sorted
				if (target>nums[mid] && target <= nums[end])
					start = mid + 1;
				else
					end = mid - 1;
			}
			else {  // left half sorted
				if (target >= nums[start] && target < nums[mid])
					end = mid - 1;
				else
					start = mid + 1;
			}
		}
		return -1;
	}
};

/*34. Search for a Range
Given an array of integers sorted in ascending order, find the starting and ending position of a given target value.
Your algorithm's runtime complexity must be in the order of O(log n).
If the target is not found in the array, return[-1, -1].
For example,
Given[5, 7, 7, 8, 8, 10] and target value 8,
return[3, 4].*/
class Solution34 {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		vector<int> range;
		range.push_back(findLeftRange(nums, target));
		range.push_back(findRightRange(nums, target));
		return range;
	}

	int findLeftRange(vector<int>& nums, int target) {
		int start = 0;
		int end = nums.size() - 1;

		while (start <= end) {
			int mid = start + (end - start) / 2;
			if (nums[mid] < target)
				start = mid + 1;
			else if (nums[mid] > target)
				end = mid - 1;
			else
				end = mid - 1; //相同也往左移
		}
		if (start >= 0 && start < nums.size() && nums[start] == target)
			return start;
		return -1;
	}

	int findRightRange(vector<int>& nums, int target) {
		int start = 0;
		int end = nums.size() - 1;

		while (start <= end) {
			int mid = start + (end - start) / 2;
			if (nums[mid] < target)
				start = mid + 1;
			else if (nums[mid] > target)
				end = mid - 1;
			else
				start = mid + 1; //相同也往右移
		}
		if (end >= 0 && end < nums.size() && nums[end] == target)
			return end;
		return -1;
	}
};

/*35. Search Insert Position
Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0

思路：Binary search的变种。如果target存在于数组中，则binary search就能找到。关键在于target不在数组中，当binary search结束时：start > end时，究竟应该如何获得插入位置。这里考察的是对base case的分析。定义insertion index为p，两种base case情况：

1. start = end = mid：
a. target < A[mid]，则我们知道p = mid。
binary search下一步会搜索A[start = mid : end = mid-1]而终止，在这一步应该返回start。
b. 反之target > A[mid]，则我们知道p = mid+1。
binary search下一步会搜索A[start = mid+1 : end = mid]而终止，这一步我们仍旧应该返回start。

2. start = end-1 = mid：
a. target < A[mid]，则我们知道p = mid。
同1a情况，查找结束start > end时，返回start
b. target > A[mid]，则我们知道p = mid+1或mid+2
binary search下一步会搜索A[start = mid+1 : end = mid+1]，即base case 1的情况。

综上所述，该问题的解法思路如下：
1. Binary search整个数组，如果在start <= end时找到了target，返回mid
2. 如果查找失败，即start > end，返回start即可。*/
class Solution35 {
public:
	int searchInsert(vector<int>& nums, int target) {
		if (nums.size() == 0)
			return 0;
		int l = 0;
		int r = nums.size() - 1;
		while (l <= r) {
			int mid = (r + l) / 2;
			if (nums[mid] == target)
				return mid;
			else if (nums[mid] < target)
				l = mid + 1;
			else if (nums[mid] > target)
				r = mid - 1;
		}
		return l; //必须是l，l正好是找不到时的插入位置
	}
};


class Solution38 {
public:
     string countAndSay(int n) {
	        if (n < 1)return "";
		       string prev = "1";
		      for (int i = 2; i <= n; i++)
			        {
			            char curChar = prev[0];
			             int times = 1;//curChar 出现的次数
			             string tmpstr;
			            prev.push_back('#');//处理边界条件
			            for (int k = 1; k < prev.size(); k++)
				             {
				                if (prev[k] == curChar)
				                    times++;
				                 else
					                {
					                     tmpstr += to_string(times);
					                    tmpstr.push_back(curChar);
					                    curChar = prev[k];
					                     times = 1;
					               }
				           }
			           prev = tmpstr;
			       }
		         return prev;
		
	}
};

/*
39. Combination Sum
Given a set of candidate numbers (C) (without duplicates) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [2, 3, 6, 7] and target 7,
A solution set is:
[
[7],
[2, 2, 3]
]

思路：递归

和3 sum那题很像，如果选定一个candidates[i]，则需要继续寻找和为target-candidate[i]的combination。由于candidates和target都为正数，当和超过或等于target时，查找中止。与3sum的思路一样，对candidate排序，并且每层递归扫描的时候需要做到去重复解：
1. 不回头扫，在扫描candidates[i]时，对candidate[i: n-1]递归查找target-candidates[i]。
2. 每层扫描的时候跳过重复的candidates。*/
class Solution39 {
public:
	vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
		vector<vector<int> > allSol;
		vector<int> sol;
		if (candidates.empty()) return allSol;
		sort(candidates.begin(), candidates.end());
		findCombSum(candidates, 0, target, sol, allSol);
		return allSol;
	}

	void findCombSum(vector<int> &candidates, int start, int target, vector<int> &sol, vector<vector<int>> &allSol) {
		if (target == 0) {
			allSol.push_back(sol);
			return;
		}

		for (int i = start; i<candidates.size(); i++) {
			if (i>start && candidates[i] == candidates[i - 1]) continue;
			if (candidates[i] <= target) {
				sol.push_back(candidates[i]);
				findCombSum(candidates, i, target - candidates[i], sol, allSol);
				sol.pop_back();
			}
		}
	}
};

/*
41. First Missing Positive
Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space.*/
class Solution41 {
public:
	int firstMissingPositive(vector<int>& nums) {
		int len = nums.size();
		int i = 0;
		while (i < len) {
			if (nums[i] != i - 1 && nums[i]>0 && nums[i] <= len && nums[i] != nums[nums[i] - 1])
				std::swap(nums[nums[i] - 1], nums[i]);
			else
				++i;
		}

		for (int j = 0; j < len; ++j) {
			if (nums[j] != j + 1)
				return j + 1;
		}
		return len + 1;
	}
};


/*43. Multiply Strings
Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2.

Note:

The length of both num1 and num2 is < 110.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer directly.

思路：

做过Plus One，Add Binary等题后，这类按位运算的题就是一个葫芦里的药了。按照最原始的按位相乘，最后移位相加的法则来计算。

3 2 1
x       4 3
_______
9 6 3
1 2 8 4
_______
1 3 8 0 3

注意：
1. m位的数字乘以n位的数字的结果最大为m+n位：
999*99 < 1000*100 = 100000，最多为3+2 = 5位数。
2. 先将字符串逆序便于从最低位开始计算。
注意：
1. 首先要注意num1[i] * num2[j]的结果应该加到ret[i+j]的位置上。
2. 其次要注意ln 17不能遗漏最高位的进位，由于此时ret中该位为0，所以只需要将carry转为字符即可。
3. 最容易遗漏的corner case是ln 22-24。如999*0 = 0000，此时需要去掉开始的0，但又需要保留最后一个0。
*/
class Solution43 {
public:
	string multiply(string num1, string num2) {
		if (num1.empty() || num2.empty())
			return "";
		reverse(num1.begin(), num1.end());
		reverse(num2.begin(), num2.end());
		string ret(num1.size() + num2.size(), '0');

		for (int i = 0; i < num1.size(); ++i) {
			int val = num1[i] - '0';
			int carry = 0;
			for (int j = 0; j < num2.size(); ++j) {
				carry += (val*(num2[j] - '0') + (ret[i + j] - '0'));
				ret[i + j] = carry % 10 + '0';
				carry /= 10;
			}
			if (carry != 0)
				ret[num2.size() + i] = carry + '0';
		}
		reverse(ret.begin(), ret.end());

		int count = 0;
		while (count < ret.size() - 1 && ret[count] == '0') count++;
		ret.erase(0, count);
		return ret;
	}
};

/*
46. Permutations*/
class Solution46 {
public:
	vector<vector<int>> permute(vector<int>& nums) {
		vector<vector<int>> allPer;
		if (nums.empty())
			return allPer;
		vector<int> per;
		vector<bool> used(nums.size(), false);
		findPermute(nums, per, used, allPer);
		return allPer;
	}

	void findPermute(vector<int>& nums, vector<int>& per, vector<bool>& used, vector<vector<int>>& allPer) {
		if (per.size() == nums.size()) {
			allPer.push_back(per);
			return;
		}

		for (int i = 0; i < nums.size(); ++i) {
			if (used[i] == true)
				continue;
			used[i] = true;
			per.push_back(nums[i]);
			findPermute(nums, per, used, allPer);
			used[i] = false;
			per.pop_back();
		}
	}
};

/*49. Group Anagrams
Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],
Return:

[
["ate", "eat","tea"],
["nat","tan"],
["bat"]
]

Anagrams指几个string有相同的字符，但不同的字符顺序。所以一个有效的检查方法是：当两个string排序以后相同，
则它们是anagrams。可以使用一个hash table，string s的key是它自己排序后的string，这样anagrams会有相同的key。
用一个vector<int>来记录相同key的string在input vector<string>中的index。最后扫描一遍hash table，当有两个或以上string有相同的key时，
将它们输出到结果。*/
class Solution49 {
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		vector<vector<string>> allStrs;
		vector<string> per;

		unordered_map<string, vector<int>> map;
		for (int i = 0; i<strs.size(); ++i) {
			string s = strs[i];
			std::sort(s.begin(), s.end());
			map[s].push_back(i);
		}

		for (unordered_map<string, vector<int>>::iterator it = map.begin(); it != map.end(); ++it) {
			if (it->second.size()>0) {
				for (int i = 0; i < it->second.size(); i++) {
					per.push_back(strs[it->second[i]]);
				}
				allStrs.push_back(per);
			}
			per.clear();
		}
		return allStrs;
	}
};

/*50. Pow(x, n)
Implement pow(x, n).

递归公式为：x^n = x^(n/2) * x^(n/2) * x^(n%2)*/
class Solution50 {
public:
	double pow(double x, int n) {
		if (n >= 0)
			return powPositive(x, n);
		else
			return 1 / powPositive(x, -n);
	}

	double powPositive(double x, int n) {
		if (n == 0) return 1; // base case
		double res = powPositive(x, n / 2);
		res *= res;
		if (n % 2) res *= x;
		return res;
	}
};

/*
51. N-Queens
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.
Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
[".Q..",  // Solution 1
"...Q",
"Q...",
"..Q."],

["..Q.",  // Solution 2
"Q...",
"...Q",
".Q.."]
]


思路：
经典8皇后问题的推广版n皇后问题。两题其实是一回事，I的难度反而更大一些。因为能解I得到所有解，必然能知道一共几个解从而能解II。
同样也是类似DFS的backtracking问题。难点在于如何判断当前某一位置是否可以放皇后，需要通过之前所有放置过的皇后位置来判断。
对已经放置的任意皇后，需要判断当前位置是否在同一行、列、对角线上这三个条件。
1. 逐行放置皇后：排除在同一行的可能。
2. 记录之前所放皇后的列坐标：col[i]=j表示第i行的皇后在第j列。这样在放置第i+1行时，只要保证col[i+1] != col[k], k=0...i 即可。
3. 对角线判断：对于任意(i1, col[i1])和(i2, col[i2])，只有当abs(i1-i2) = abs(col[i1]-col[i2])时，两皇后才在同一对角线。*/
class Solution51 {
public:
	vector<vector<string>> solveNQueens(int n) {
		vector<vector<string>> allSol;
		vector<string> sol;
		vector<int> col;
		solveNQ(n, 0, col, sol, allSol);
		return allSol;
	}

	void solveNQ(int n, int irow, vector<int> &col, vector<string> &sol, vector<vector<string>> &allSol) {
		if (n == irow) {
			allSol.push_back(sol);
			return;
		}

		for (int icol = 0; icol < n; ++icol) {
			if (validPos(col, irow, icol)) {
				string s(n, '.');
				s[icol] = 'Q';
				sol.push_back(s);
				col.push_back(icol);
				solveNQ(n, irow + 1, col, sol, allSol);
				sol.pop_back();
				col.pop_back();
			}
		}
	}

	bool validPos(vector<int> &col, int irow, int icol) {
		for (int i = 0; i < col.size(); ++i) {
			if (icol == col[i] || abs(irow - i) == abs(icol - col[i]))
				return false;
		}
		return true;
	}
};

/*
52. N-Queens II
Follow up for N-Queens problem.

Now, instead outputting board configurations, return the total number of distinct solutions.
同上一题（51.N-Queens）*/
class Solution52 {
public:
	int totalNQueens(int n) {
		vector<int> col;
		int totSol = 0;
		solveNQ(n, 0, col, totSol);
		return totSol;
	}

	void solveNQ(int n, int irow, vector<int> &col, int &totSol) {
		if (irow == n) {
			totSol++;
			return;
		}

		for (int icol = 0; icol < n; icol++) {
			if (validPos(col, irow, icol)) {
				col.push_back(icol);
				solveNQ(n, irow + 1, col, totSol);
				col.pop_back();
			}
		}
	}

	bool validPos(vector<int> &col, int irow, int icol) {
		if (irow < col.size()) return false;
		for (int i = 0; i < col.size(); i++) {
			if (icol == col[i] || abs(irow - i) == abs(icol - col[i]))
				return false;
		}
		return true;
	}
};

/*
53. Maximum Subarray
Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.

思路：dp
状态转移方程： sum[i]=max(sum[i-1]+a[i],a[i])*/
class Solution53 {
public:
	int maxSubArray(vector<int>& nums) {
		int len = nums.size();
		if (len <= 0) return 0;
		int maxSum = nums[0];
		int curSum = nums[0];
		for (int i = 1; i < len; ++i) {
			if (curSum <= 0)
				curSum = nums[i]; //如果前面位置最大连续子序列和小于等于0，则以当前位置i结尾的最大连续子序列和为a[i]
			else
				curSum += nums[i]; //如果前面位置最大连续子序列和大于0，则以当前位置i结尾的最大连续子序列和为它们两者之和 
			maxSum = max(maxSum, curSum);
		}
		return maxSum;
	}
};

/*
55. Jump Game
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

思路：Jump Game I

注意题目中A[i]表示的是在位置i，“最大”的跳跃距离，而并不是指在位置i只能跳A[i]的距离。所以当跳到位置i后，
能达到的最大的距离至少是i+A[i]。用greedy来解，记录一个当前能达到的最远距离maxIndex：

1. 能跳到位置i的条件：i<=maxIndex。
2. 一旦跳到i，则maxIndex = max(maxIndex, i+A[i])。
3. 能跳到最后一个位置n-1的条件是：maxIndex >= n-1
*/
class Solution55 {
public:
	bool canJump(int A[], int n) {
		int maxIndex = 0;
		for (int i = 0; i<n; i++) {
			if (i>maxIndex || maxIndex >= (n - 1)) break;
			maxIndex = max(maxIndex, i + A[i]);
		}
		return maxIndex >= (n - 1) ? true : false;
	}
};


/*57. Insert Interval
Wednesday, November 26, 2014
[LeetCode] Insert Interval
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
You may assume that the intervals were initially sorted according to their start times.
Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].
This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].

思路：

题目涉及两个问题：
1. 如何判断两个interval有重合。
2. 如果重合，如何合并。
3. 如何判断[s1, e1]是否在[s2, e2]前面

A1. 两个interval有重合有很多种可能性，但判断它们不重合则比较简单直观。无非两种情况：

(1) [s1, e1]  [s2, e2]：即s2>e1
(2) [s2, e2]  [s1, e1]：即s1>e2

不重合的条件为：s2>e1 || s1>e2，反之则重合。

A2. 对于两个有重合的interval： [s1, e1]，[s2, e2]。合并后变为[min(s1,s2), max(e1,e2)]。

A3. [s1, e1]在[s2, e2]前面的条件：e1<s2

所以插入interval a的算法为：扫描队列中每个interval I[i]：
如果a已经被插入了，则只要插入I(i)就行。
如果a在I(i)前，则先插入a再插入I(i)到结果。
如果a和I(i)有重合，则将I(i)合并入a，但并不插入结果。
如果a在I(i)后，则插入I(i)到结果。*/
 struct Interval {
     int start;
     int end;
     Interval() : start(0), end(0) {}
     Interval(int s, int e) : start(s), end(e) {}
 };

class Solution57 {
public:
	vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
		vector<Interval> ret;
		bool bInserted = false;
		for (int i = 0; i < intervals.size(); ++i) {
			if (bInserted) {
				ret.push_back(intervals[i]);
				continue;
			}

			if (newInterval.end < intervals[i].start) {
				ret.push_back(newInterval);
				ret.push_back(intervals[i]);
				bInserted = true;
				continue;
			}

			// combine newInterval with current interval
			if (newInterval.start <= intervals[i].end && intervals[i].start <= newInterval.end) {
				newInterval.start = min(newInterval.start, intervals[i].start);
				newInterval.end = max(newInterval.end, intervals[i].end);
				continue;
			}

			ret.push_back(intervals[i]);
		}
		if (!bInserted) ret.push_back(newInterval);
		return ret;
	}
};

/*59. Spiral Matrix II
Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

For example,
Given n = 3,

You should return the following matrix:
[
[ 1, 2, 3 ],
[ 8, 9, 4 ],
[ 7, 6, 5 ]
]*/
class Solution59 {
public:
	vector<vector<int>> generateMatrix(int n) {
		vector<vector<int>> ret(n, vector<int>(n, 0));
		int count = n / 2;
		int val = 1;
		for (int i = 0; i < count; ++i) {
			int last = n - 1 - i;
			for (int j = i; j<last; j++)
				ret[i][j] = val++;
			for (int j = i; j<last; j++)
				ret[j][last] = val++;
			for (int j = last; j>i; j--)
				ret[last][j] = val++;
			for (int j = last; j>i; j--)
				ret[j][i] = val++;
		}
		if (n % 2 == 1)
			ret[n / 2][n / 2] = val;
		return ret;
	}
};


class Solution62 {
public:
	int uniquePaths(int m, int n) {
		if (m < 1 && n < 1)
			return 0;
		vector<vector<int> > dp(m, vector<int>(n, 1));
		for (int i=1; i < m; ++i) {
			for (int j=1; j < n; ++j) {
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}
		return dp[m - 1][n - 1];
	}
};