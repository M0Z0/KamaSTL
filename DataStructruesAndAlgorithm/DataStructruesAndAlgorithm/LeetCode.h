#include <vector>
#include <algorithm>
#include <string>
#include <list>
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