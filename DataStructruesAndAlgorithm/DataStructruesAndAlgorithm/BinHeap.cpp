#include "BinHeap.h"
#include "fatal.h"
#include <stdlib.h>

const int MinPQSize = 10;
const int MinData = -32767;

namespace BH{

	struct HeapStruct
	{
		int Capacity;
		int Size;
		ElementType *Elements;
	};

	PriorityQueue Initialize(int MaxElements)
	{
		if (MaxElements < MinPQSize)
			Error("too small");

		PriorityQueue H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
		if (NULL == H)
			FatalError("out of space!");

		H->Elements = (ElementType*)malloc((MaxElements + 1)
			*sizeof(ElementType));

		if (NULL == H->Elements)
			FatalError("out of space!");

		H->Capacity = MaxElements;
		H->Size = 0;
		H->Elements[0] = MinData;

		return H;
	}

	void Insert(ElementType X, PriorityQueue H)
	{
		if (IsFull(H))
		{
			Error("full");
			return;
		}

		int i = 0;
		for (i = ++H->Size; H->Elements[i / 2] > X; i/=2)
			H->Elements[i] = H->Elements[i / 2];
		H->Elements[i] = X;
	}

	ElementType DeleteMin(PriorityQueue H)
	{
		ElementType MinElement, LastElement;

		if (IsEmpty(H))
		{
			Error("Is empty");
			return H->Elements[0];
		}

		MinElement = H->Elements[1];
		LastElement = H->Elements[--H->Size];

		int i, Child;
		for (i = 1; i * 2 < H->Size; i=Child)
		{
			Child = i * 2;
			// Find smaller child
			if (Child != H->Size
				&& H->Elements[Child + 1] < H->Elements[Child])
				++Child;

			if (LastElement > H->Elements[Child])
				H->Elements[i] = H->Elements[Child];
			else
				break;
		}
		H->Elements[i] = LastElement;
		return MinElement;
	}

	void MakeEmpty(PriorityQueue H)
	{
		H->Size = 0;
	}

	int IsEmpty(PriorityQueue H)
	{
		return H->Size == 0;
	}

	int IsFull(PriorityQueue H)
	{
		return H->Size == H->Capacity;
	}

	void Destroy(PriorityQueue H)
	{
		free(H->Elements);
		free(H);
	}

	ElementType FindMin(PriorityQueue H)
	{
		if (!IsEmpty(H))
			return H->Elements[1];
		Error("Is empty");
		return H->Elements[0];
	}
}