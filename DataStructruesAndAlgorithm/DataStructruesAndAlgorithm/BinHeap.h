#ifndef _BIN_HEAP_H
#define _BIN_HEAP_H

typedef int ElementType;
namespace BH
{
	struct HeapStruct;
	typedef struct HeapStruct *PriorityQueue;
	PriorityQueue Initialize(int MaxElements);
	void Destroy(PriorityQueue H);
	void MakeEmpty(PriorityQueue H);
	void Insert(ElementType X, PriorityQueue H);
	ElementType DeleteMin(PriorityQueue H);
	ElementType FindMin(PriorityQueue H);
	int IsEmpty(PriorityQueue H);
	int IsFull(PriorityQueue H);

#endif // !_BIN_HEAP_H
