#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "list.h"


int main()
{
	/*List* lst = createList();*/
	List* lst = NULL;
	int choose, size;
	do
	{
		Node* p;
		printf("Select  an action:\n");
		scanf("%d", &choose);
		int index;
		if (choose == 6 || choose == 7 || choose == 8 || choose == 9 || choose == 13)
		{
			printf("Enter an index\n");
			scanf("%d", &index);
		}
		switch (choose)
		{
		case 1:
			lst = createList();
			break;
		case 2:
			p = malloc(sizeof(Node));
			pushBack(lst, p);
			break;
		case 3:
			p = malloc(sizeof(Node));
			pushFront(lst, p);
			break;
		case 4:
			popBack(lst);
			break;
		case 5:
			popFront(lst);
			break;
		case 6:
			p = GetList(lst, index);
			printf("#\tp\t\t\tprev\t\t\tnext\n");
			printf("%d\t%p\t%p\t%p\n", 0, p, p->pPrev, p->pNext);
			break;
		case 7:
			p = Remove(lst, index);
			printf("#\tp\t\t\tprev\t\t\tnext\n");
			printf("%d\t%p\t%p\t%p\n", 0, p, p->pPrev, p->pNext);
			break;
		case 8:
			erase(lst, index);
			break;
		case 9:
			int count;
			printf("Enter a count\n");
			scanf("%d", &count);
			Erase(lst, index, count);
			break;
		case 10:
			printList(lst);
			break;
		case 11:
			size = Size(lst);
			printf("Size = %d \n", size);
			break;
		case 12:
			clear(&lst);
			break;
		case 13:
			p = malloc(sizeof(Node));
			insert(lst, index, p);
			break;
		}
	} while (choose != 0);
	return 0;
}