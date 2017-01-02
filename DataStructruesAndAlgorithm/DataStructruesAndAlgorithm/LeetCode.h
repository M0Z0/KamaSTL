#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <map>
#include <stack>
#include <queue> 
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
				//��һ�л����һ�У�ʹ�ù�ʽ1��  
				if (i == 0 || i == numRows - 1)
				{
					indx += 2 * numRows - 2;
				}
				//�м��У��ж���ż��ʹ�ù�ʽ2��3  
				else
				{
					if (k & 0x1)  //����λ  
						indx += 2 * (numRows - 1 - i);
					else indx += 2 * i;
				}

				//�ж�indx�Ϸ���  
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
			else if (str[i] == '-' && bNofirst == false) //����ǰ�ĺϷ��ַ��Ǹ���
				bNegative = true;
			else if (str[i] == '+' && bNofirst == false) //����ǰ�ĺϷ��ַ�������
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
�������ֹ���
1�� �������ֹ���7������I��1����V��5����X��10����L��50����C��100����D��500����M��1000����
����������û�С�0����
2�� �ظ�������һ��������������ظ�3�Ρ�
3�� �Ҽ������
�ڽϴ���������ֵ��ұ߼��Ͻ�С���������֣���ʾ�����ּ�С���֡�
�ڽϴ���������ֵ���߼��Ͻ�С���������֣���ʾ�����ּ�С���֡�
4�� ��������������ƣ�������I��X��C���ҷ��ڴ��������ֻ����һ����
(*) V �� X ��ߵ�С����ֻ���â�
(*) L �� C ��ߵ�С����ֻ����X��
(*) D �� M �� �ߵ�С����ֻ����C��*/
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

class Solution16 { //��sum2����
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
		p = q; //���°�ָ��ָ��ͷ
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
		return parStack.empty(); //�˴�Ӧ�ж��Ƿ�Ϊ��
	}
};

/*21. Merge Two Sorted Lists
Merge two sorted linked lists and return it as a new list.The new list should be made by splicing together the nodes of the first two lists.*/
class Solution21 {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) { //l3ָ��ÿ��һ�ȽϵĽ�С��㣬�͹鲢��������
		ListNode* l3 = new ListNode(-1); //�ý����ʱ�ģ��ڶ���������Ŀ��listͷ
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
��ÿ��list����С�ڵ����һ��priority queue (min heap)�С�֮��ÿ��queue��ȡ��һ���ڵ㣬�򽫸ýڵ�����list�е���һ���ڵ���룬�Դ�����ֱ��ȫ���ڵ㶼����priority queue������priority queue�Ĵ�СΪʼ��Ϊk����ÿ�β���ĸ��Ӷ���log k��һ�������nk���ڵ㡣ʱ�临�Ӷ�ΪO(nk logk)���ռ临�Ӷ�ΪO(k)��
ע��C++��STL�е�priority queueĬ����max heap������һ���µıȽϺ�����*/
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