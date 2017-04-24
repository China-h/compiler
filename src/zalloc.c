#include <stdio.h>
#include <stdlib.h>

#include <zalloc.h>
#include <algorithm.h>

#define ALIGNSIZE 4

/*空闲链表*/
static struct mblock *FreeBlochs = NULL;


/*初始化头*/
void InitHeap(Heap hp)
{
	hp->last = &hp->head;
	hp->head.next=NULL;
	hp->head.end = hp->head.avail = hp->head.being = NULL;
}

/*释放链表*/
void FreeHeap(Heap hp)
{
	hp->last->next = FreeBlochs;
	FreeBlochs = hp->head.next;
	InitHeap(hp);
}


/*从空闲链表中取得大于size的内存块，没有则返回NULL*/
struct mblock *GetFreeBloch(int size)
{
	struct mblock *blk,*tmp;

	/*如果空闲链表为空，返回空*/
	if (FreeBlochs == NULL) return NULL;

	tmp = FreeBlochs;
	while ((tmp->end - tmp->being) < size)
	{
		blk = tmp;
		tmp = tmp->next;
		if (tmp == NULL) break;
	}
	if (tmp != NULL)
	{
		if (tmp == FreeBlochs)
		{
			FreeBlochs = FreeBlochs->next;
			blk = tmp;
		}
		else
		{
			blk->next = tmp->next;
			blk = tmp;
		}
	}
	else
		blk = NULL;
	return blk;
}

void *HeapAllocate(Heap hp,int size)
{
    struct mblock *blk;
    char *p = NULL;
    int m;
    blk = hp->last;
    if ((blk->end - blk->avail) > size)
	{
		/*从最后一块分配*/

		p = blk->avail;
		blk->avail = blk->avail + size;
		return p;
	}
	if ((blk = GetFreeBloch(size)) != NULL)
	{
		/*从空闲链表分配*/

		p = blk->being;
		blk->avail = blk->being + size;
		return p;
	}
	else
	{
		/*系统申请*/

		m = sizeof(struct mblock) + size + 1;
		m = ALIGN(m,ALIGNSIZE);
		blk = (struct mblock*)malloc(m);
		if (blk == NULL)
		{
				//错误处理，未完成
				printf("内存申请失败\n");
				exit(-1);
		}
		p = (char*)(blk + 1);
		blk->being = p;
		blk->end = p + m - sizeof(struct mblock);
		blk->avail = p + size;
		return p;
	}
}
