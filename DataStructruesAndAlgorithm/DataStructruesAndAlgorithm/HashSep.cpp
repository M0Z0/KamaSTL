#include "fatal.h"
#include "HashSep.h"
#include <stdlib.h>

const int MinTableSize = 10;

struct ListNode
{
	ElementType Element;
	Position Next;
};

typedef Position List;

struct  HashTbl
{
	int TableSize;
	List *TheLists;
};

static int NextPrime(int n)
{
	int i;
	if (n % 2 == 0)
		n++;
	for ( ; ; n += 2)
	{
		for (i = 3; i*i <= n; i+=2)
		{
			if (n%i == 0)
				goto ContOuter;
		}
		return n;
	ContOuter: ;
	}
}

Index Hash(ElementType key, int TableSize)
{
	return key % TableSize;
}

HashTable InitializeTable(int TableSize)
{
	HashTable H;
	int i;

	if (TableSize < MinTableSize)
	{
		Error("Table size too small");
		return NULL;
	}

	H = (HashTable)malloc(sizeof(struct HashTbl));
	if (H == NULL)
		FatalError("Out of space!!!");

	H->TableSize = NextPrime(TableSize);

	H->TheLists = (List*)malloc(sizeof(List)*H->TableSize);
	if (H->TheLists == NULL)
		FatalError("Out of Space!!!");

	for (i = 0; i < H->TableSize; i++)
	{
		H->TheLists[i] = (List)malloc(sizeof(struct ListNode));
		if (H->TheLists[i] == NULL)
			FatalError("Out of space!!!");
		else
			H->TheLists[i]->Next = NULL;
	}

	return H;
}

Position Find(ElementType key, HashTable H)
{
	Position p;
	List L;

	L = H->TheLists[Hash(key, H->TableSize)];
	p = L->Next;
	while (p != NULL && p->Element != key)
		p = p->Next;
	return p;
}

void insert(ElementType Key, HashTable H)
{
	Position pos, newCell;
	List l;

	pos = Find(Key, H);
	if (NULL == pos)
	{
		newCell = (List)malloc(sizeof(struct ListNode));
		if (NULL == newCell)
			FatalError("Out of space!!!");
		else
		{
			l = H->TheLists[Hash(Key, H->TableSize)];
			newCell->Next = l->Next;
			newCell->Element = Key;
			l->Next = newCell;
		}
	}
}

ElementType Retrieve(Position p)
{
	return p->Element;
}

void DestroyTable(HashTable h)
{
	for (int i = 0; i < h->TableSize; i++)
	{
		Position p = h->TheLists[i];
		Position tmp;

		while (p != NULL)
		{
			tmp = p->Next;
			free(p);
			p = tmp;
		}
	}
	free(h->TheLists);
	free(h);
}