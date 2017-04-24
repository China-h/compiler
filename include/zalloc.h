/*内存管理模块*/

#ifndef _ZALLOC_H
#define _ZALLOC_H

struct mblock
{
	struct mblock *next;
	char *being;
	char *avail;
	char *end;
};

struct heap
{
	struct mblock *last;
	struct mblock head;
};

typedef struct heap* Heap;

extern void InitHeap(Heap hp);
extern void FreeHeap(Heap hp);
extern void *HeapAllocate(Heap hp,int size);

#endif //ZALLOC_H
