#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <map>
#include <stack>
#include <queue> 
#include <map>
#include <xfunctional>
#include <set>
#include <unordered_map>
using namespace std;
//23.从上往下打印二叉树，一层一层打印
struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

void PrintFromTopToBottom(BinaryTreeNode* pTreeRoot)
{
	deque<BinaryTreeNode*> dequeTreeNode;
	if (pTreeRoot != NULL)
		dequeTreeNode.push_back(pTreeRoot);
	while (dequeTreeNode.size())
	{
		BinaryTreeNode* pNodeTmp = dequeTreeNode.front();
		dequeTreeNode.pop_front();
		printf("%d ", pNodeTmp->m_nValue);

		if (pNodeTmp->m_pLeft != NULL)
			dequeTreeNode.push_back(pNodeTmp->m_pLeft);
		if (pNodeTmp->m_pRight != NULL)
			dequeTreeNode.push_back(pNodeTmp->m_pRight);
	}
}

typedef multiset<int, greater<int>> intSet;
typedef multiset<int, greater<int>>::iterator setIterator;
//30.最小的K个数
void GetLeastNumbers(const vector<int>& data, intSet& leastNumbers, int k)
{
	leastNumbers.clear();
	if (k < 1 || data.size() < k)
		return;

	vector<int>::const_iterator iter = data.begin();
	for (; iter != data.end(); ++iter)
	{
		if ((leastNumbers.size()) < k)
			leastNumbers.insert(*iter);
		else
		{
			setIterator iterGreater = leastNumbers.begin();
			if (*iter<*(leastNumbers.begin()))
			{
				leastNumbers.erase(iterGreater);
				leastNumbers.insert(*iter);
			}
		}
	}
}

//39.二叉树的深度
int TreeDepth(BinaryTreeNode* pTreeRoot)
{
	if (pTreeRoot == NULL)
		return 0;

	int nLeft = TreeDepth(pTreeRoot->m_pLeft);
	int nRight = TreeDepth(pTreeRoot->m_pRight);
	return nLeft > nRight ? (nLeft + 1) : (nRight + 1);
}