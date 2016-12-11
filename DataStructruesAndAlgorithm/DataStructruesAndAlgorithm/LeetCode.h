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
class Solution {
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