#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Node
{
	struct Node* pNext;
	struct Node* pPrev;

}Node;
typedef struct DbList
{
	size_t size;
	Node* head;
	Node* tail;
}List;

List* createList();
void pushFront(List* lst,Node *temp);
void pushBack(List* lst,Node *temp);
void popFront(List* list);
void popBack(List* lst);
void printList(List* lst);
Node* GetList(List* list, const size_t index);
void insert(List* list, const size_t index,Node *temp);
void Erase(List* list, const size_t index, size_t number);
void erase(List* list, const size_t index);
//void ReSize(List* lst, const size_t NewSize);
void clear(List** lst);
const size_t Size(List* lst);
Node* Remove(List* lst, size_t index);

List* createList()
{
	List* tmp = (List*)malloc(sizeof(List));
	tmp->size = 0;
	tmp->head = tmp->tail = NULL;
	return tmp;
}
void pushFront(List* lst,Node *temp)
{
	if (lst)
	{
		if (temp == NULL)
			return;
		temp->pNext = lst->head;
		temp->pPrev = NULL;
		if (lst->head)
			lst->head->pPrev = temp;
		lst->head = temp;
		if (lst->tail == NULL)
			lst->tail = temp;
		lst->size++;
	}
	else
		printf("Error!\n Memory not allocated\n");
}
void pushBack(List* lst,Node *temp)
{
	if (lst)
	{
		if (temp == NULL)
			return;
		temp->pNext = NULL;
		temp->pPrev = lst->tail;
		if (lst->tail)
		{
			lst->tail->pNext = temp;
		}
		lst->tail = temp;
		if (lst->head == NULL)
			lst->head = temp;
		lst->size++;
	}
	else
		printf("Error! Memory not allocated\n");
}
void popFront(List* list)
{
	if (list)
	{
		if (list->head == NULL)
			return;
		Node* prev;
		prev = list->head;
		list->head = list->head->pNext;
		if (list->head)
			list->head->pPrev = NULL;
		if (prev == list->tail)
			list->tail = NULL;
		free(prev);
		list->size--;
	}
	else
		printf("Error!size = 0 or memory not allocated\n");
}
void popBack(List* lst)
{
	if (lst)
	{
		if (lst->tail == NULL)
			return;
		Node* prev;
		prev = lst->tail;
		lst->tail = lst->tail->pPrev;
		if (lst->tail)
			lst->tail->pNext = NULL;
		if (prev == lst->head)
			lst->head = NULL;
		free(prev);
		lst->size--;
	}
	else
		printf("Error! size =0 or memory not allocated!\n");
}
Node* Remove(List* lst, size_t index)
{
	if (index < lst->size && index >= 0)
	{
		Node* tmp = GetList(lst, index);
		if (tmp->pPrev)
			tmp->pPrev->pNext = tmp->pNext;
		if (tmp->pNext)
			tmp->pNext->pPrev = tmp->pPrev;
		if (!tmp->pNext)
			lst->tail = tmp->pPrev;
		if (!tmp->pPrev)
			lst->head = tmp->pNext;
		lst->size--;
		return tmp;
	}
	else
		printf("Error! index doesn't match\n");
}

void printList(List* lst)
{
	if (lst->size != 0)
	{
		int i = 0;
		Node* tmp;
		printf("List: %p\tHead: %p\tTail: %p\n", lst, lst->head, lst->tail);
		printf("#\tp\t\tprev\t\tnext\n");
		for (tmp = lst->head; tmp; tmp = tmp->pNext, i++)
			printf("%d\t%p\t%p\t%p\n", i, tmp, tmp->pPrev, tmp->pNext);
	}
	else
		printf("Error!Size  = 0\n");
}
Node* GetList(List* list, const size_t index)
{
	if (index < list->size && index >= 0)
	{
		Node* tmp = NULL;
		size_t i;
		if (index <= list->size / 2)
		{
			i = 0;
			tmp = list->head;
			while (tmp && i < index)
			{
				tmp = tmp->pNext;
				i++;
			}
		}
		else
		{
			i = list->size - 1;
			tmp = list->tail;
			while (tmp && i > index)
			{
				tmp = tmp->pPrev;
				i--;
			}
		}
		return tmp;
	}
	else
	{
		printf("Not valid index\n");
		return NULL;
	}
}

void insert(List* list, const size_t index,Node *temp)
{
	Node* tmp;
	if (tmp = GetList(list,index))
	{
		Node* elm = temp;
		Node* prev = tmp->pPrev;
		elm->pPrev = tmp->pPrev;
		elm->pNext = tmp;
		if (tmp->pNext)
			tmp->pNext->pPrev = elm;
		prev->pNext = elm;
		tmp->pPrev = elm;
		if (!tmp->pPrev)
			list->head = tmp;
		if (!tmp->pNext)
			list->tail = tmp;
		list->size++;
	}
	else if (index == 0)
		pushFront(list,temp);
	else if (index == list->size)
		pushBack(list,temp);
}
const size_t Size(List* lst)
{
	return lst->size;
}
//void ReSize(List* lst, const size_t NewSize)
//{
//	size_t temp = lst->size;
//	if (NewSize < lst->size)
//	{
//		for (int i = 0; i < temp - NewSize; i++)
//			popBack(lst);
//	}
//	else
//	{
//		for (int i = 0; i < NewSize - temp; i++)
//			pushBack(lst);
//	}
//}
void erase(List* list, const size_t index)
{
	if (list->size == 1 || index - 1 == list->size)
		popBack(list);
	if (index == 0)
		popFront(list);
	else
	{
		Node* tmp = GetList(list, index);
		if (tmp->pPrev)
			tmp->pPrev->pNext = tmp->pNext;
		if (tmp->pNext)
			tmp->pNext->pPrev = tmp->pPrev;
		if (!tmp->pNext)
			list->tail = tmp->pPrev;
		if (!tmp->pPrev)
			list->head = tmp->pNext;
		free(tmp);
		list->size--;
	}
}
void Erase(List* list, const size_t index, size_t number)
{

	if (index < list->size)
	{
		if (number > list->size)
			number = list->size;
		for (int i = 0; i < number; i++)
			erase(list, index);
	}
}

void clear(List** lst)
{
	if ((*lst))
	{
		Node* tmp = (*lst)->head;
		Node* next = NULL;
		while (tmp)
		{
			next = tmp->pNext;
			free(tmp);
			tmp = next;
		}
		free(*lst);
		(*lst) = NULL;
	}
}
int main()
{
	/*List* lst = createList();*/
	List* lst = NULL;
	int choose,size;
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
			pushBack(lst,p);
			break;
		case 3:
			p = malloc(sizeof(Node));
			pushFront(lst,p);
			break;
		case 4:
			popBack(lst);
			break;
		case 5:
			popFront(lst);
			break;
		case 6:
			 p = GetList(lst,index);
			printf("#\tp\t\t\tprev\t\t\tnext\n");
			printf("%d\t%p\t%p\t%p\n", 0, p, p->pPrev, p->pNext);
			break;
		case 7:
			p = Remove(lst,index);
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