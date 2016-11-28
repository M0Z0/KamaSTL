#ifndef _LEFT_HEAP_H
#define _LEFT_HEAP_H

namespace LeftHeap
{
	struct TreeNode;
	typedef int ElementType;
	typedef struct TreeNode *PriorityQueue;

	PriorityQueue Initialize();
	ElementType FindMin(PriorityQueue H);
	int IsEmpty(PriorityQueue H);
	PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2);

#define Insert(X, H) (H = Insert1((X), H))

	PriorityQueue Insert1(ElementType X, PriorityQueue H);
	PriorityQueue DeleteMin1(PriorityQueue H);
}
#endif
