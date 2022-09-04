
#include <stdio.h>
#include <malloc.h>


typedef struct Node
{
	int data;
	struct Node* pNext;
	struct Node* pPrev;
	
}Node;
typedef struct DbList
{
	size_t size;
	Node* head;
	Node* tail;
}List;

List* createList(List* lst);
void pushFront(List* lst, int value);
void pushBack(List* lst, int value);
void* popFront(List* list);
void* popBack(List* lst);
void printList(List* lst);
Node* GetList(List* list, size_t index);
void insert(List* list, size_t index, int value);
void* Erase(List* list, size_t index, size_t number);
void* erase(List* list, size_t index);

List *createList(List* lst)
{
	List* tmp = (List*)malloc(sizeof(List));
	tmp->size = 0;
	tmp->head = tmp->tail = NULL;
	return tmp;
}
void pushFront(List* lst, int value)
{
	Node* tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL)
		return;
	tmp->data = value;
	tmp->pNext = lst->head;
	tmp->pPrev = NULL;
	if (lst->head)
		lst->head->pPrev = tmp;
	lst->head = tmp;
	if (lst->tail == NULL)
		lst->tail = tmp;
	lst->size++;
}
void pushBack(List* lst, int value)
{
	Node* tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL)
		return;
	tmp->data = value;
	tmp->pNext = NULL;
	tmp->pPrev = lst->tail;
	if (lst->tail)
	{
		lst->tail->pNext = tmp;
	}
	lst->tail = tmp;
	if (lst->head == NULL)
		lst->head = tmp;
	lst->size++;
}
void *popFront(List* list)
{
	Node* tmp = list->head;
	list->head = list->head->pNext;
	 free(tmp);
	list->size--;
	/*if (list->head == NULL)
		return;
	if (list->size == 1)
		free(list);
	Node* prev;
	prev = list->head;
	list->head = list->head->pNext;
	if (list->head)
		list->head->pPrev = NULL;
	if (prev == list->tail)
		list->tail = NULL;*/

	//f/*ree(prev);
	//list->size--;*/
	
}
void* popBack(List* lst)
{
	if (lst->tail == NULL)
		return;
	void* tmp;
	Node* prev;
	prev = lst->tail;
	lst->tail = lst->tail->pPrev;
	if (lst->tail)
		lst->tail->pNext = NULL;
	if (prev == lst->head)
		lst->head = NULL;
	tmp = prev->data;
	free(prev);
	lst->size--;
	return tmp;
}
void printList(List* lst)
{
	if (lst->size != 0)
	{
		int i = 0;
		Node* tmp;
		printf("List: %p\tHead: %p\tTail: %p\n",lst,lst->head,lst->tail);
		printf("#\tp\t\tprev\t\tnext\n");
		for (tmp= lst->head; tmp;tmp = tmp->pNext,i++)
			printf("%d\t%p\t%p\t%p\n",i,tmp,tmp->pPrev,tmp->pNext);
	}
	else
		printf("Error!Size  == 0");
}
Node* GetList(List* list, size_t index)
{
	index--;
	Node* tmp = NULL;
	size_t i;
	if (index < list->size / 2)
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
void insert(List* list, size_t index, int value)
{
	if (list->size >= 1 && index > 0 && index <=list->size)
	{
		Node* tmp = GetList(list, index);
		Node* elm = NULL;
		elm = (Node*)malloc(sizeof(Node));
		elm->data = value;
		elm->pPrev = tmp;
		elm->pNext = tmp->pNext;
		if (tmp->pNext)
			tmp->pNext->pPrev = elm;
		tmp->pNext = elm;
		if (!tmp->pPrev)
			list->head = tmp;
		if (!tmp->pNext)
			list->tail = tmp;
		list->size++;
	}
	else if (index == 0)
		pushFront(list, value);
	else if (index == list->size)
		pushBack(list, value);
}
size_t Size(List *lst)
{
	return lst->size;
}
void ReSize(List* lst, size_t NewSize)
{
	int temp = lst->size;
	if (NewSize < lst->size)
	{
		for (int i = 0; i < temp - NewSize; i++)
			popBack(lst);
	}
	else
	{
		for (int i = 0; i < NewSize- temp; i++)
			pushBack(lst,0);
	}
}
void *erase(List* list, size_t index)
{
	if (list->size == 1 || index - 1 == list->size)
		popBack(list);
	if (index == 0)
		popFront(list);
	else
	{
		Node* tmp = GetList(list, index);
		void* value = NULL;
		if (tmp->pPrev)
			tmp->pPrev->pNext = tmp->pNext;
		if (tmp->pNext)
			tmp->pNext->pPrev = tmp->pPrev;
		value = tmp->data;
		if (!tmp->pNext)
			list->tail = tmp->pPrev;
		if (!tmp->pPrev)
			list->head = tmp->pNext;
		free(tmp);
		list->size--;

	}
}
void* Erase(List* list, size_t index, size_t number)
{
	for (int i = 0; i < number; i++)
		erase(list, index);
}
void deletemem(List** lst)
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
int main()
{
	List *lst = createList(&lst);
	pushFront(lst, 40);
	insert(lst, 0, 50);
	printList(lst);
	deletemem(&lst);
	return 0;
}
