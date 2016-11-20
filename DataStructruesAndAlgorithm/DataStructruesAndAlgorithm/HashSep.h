#ifndef _HASH_SEP_H
#define _HASH_SEP_H

typedef int ElementType;
typedef unsigned int Index;

	struct ListNode;
	typedef struct ListNode *Position;
	struct HashTbl;
	typedef struct HashTbl *HashTable;

	HashTable InitializeTable(int TableSize);
	void DestroyTable(HashTable h);
	Position Find(ElementType key, HashTable h);
	void insert(ElementType key, HashTable h);
	ElementType Retrieve(Position p);


#endif // !_HASH_SEP_H
