#include "LeftHeap.h"
#include <stdio.h>
#include <stdlib.h>
#include "fatal.h"

namespace LeftHeap{

	struct TreeNode
	{
		ElementType Element;
		PriorityQueue Left;
		PriorityQueue Right;
		int Npl;
	};

	PriorityQueue Initialize()
	{
		return NULL;
	}

	int IsEmpty(PriorityQueue H)
	{
		return H == NULL;
	}

	void SwapChildren(PriorityQueue H)
	{
		PriorityQueue tmp;
		tmp = H->Left;
		H->Left = H->Right;
		H->Right = tmp;
	}

	static PriorityQueue Merge1(PriorityQueue H1, PriorityQueue H2);

	PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2)
	{
		if (H1 == NULL)
			return H2;
		if (H2 == NULL)
			return H1;
		if (H1->Element < H2->Element)
			return Merge1(H1, H2);
		else
			return Merge1(H2, H1);
	}

	static PriorityQueue Merge1(PriorityQueue H1, PriorityQueue H2)
	{
		if (H1->Left == NULL)	//因为是左式堆，若左儿子为null，那么右儿子必然也为null
			H1->Left = H2;
		else{				    //H1是根值较小的堆，故递归合并它的右子树与H2；
			H1->Right = Merge(H1->Right, H2);
			if (H1->Left->Npl < H1->Right->Npl)
				SwapChildren(H1);
			H1->Npl = H1->Right->Npl + 1;
		}
		return H1;
	}

	PriorityQueue Insert1(ElementType X, PriorityQueue H)
	{
		PriorityQueue SingleNode;
		SingleNode = (TreeNode*)malloc(sizeof(struct  TreeNode));
		if (SingleNode == NULL)
			Error("Out of space");
		else
		{
			SingleNode->Element = X;
			SingleNode->Npl = 0;
			SingleNode->Left = SingleNode->Right = NULL;
			H = Merge(SingleNode, H);
		}
		return H;
	}

	PriorityQueue DeleteMin(PriorityQueue H)
	{
		PriorityQueue LeftHeap, RightHeap;
		if (IsEmpty(H))
		{
			FatalError("Priority queue is empty");
			return H;
		}
		LeftHeap = H->Left;
		RightHeap = H->Right;
		free(H);
		return Merge(LeftHeap, RightHeap);
	}
}