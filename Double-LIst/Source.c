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
Node* GetNth(List* list, size_t index);
void insert(List* list, size_t index, int value);

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
	if (list->head == NULL)
		return;
	if (list->size == 1)
		free(list);
	void* tmp;
	Node* prev;
	prev = list->head;
	list->head = list->head->pNext;
	if (list->head)
		list->head->pPrev = NULL;
	if (prev == list->tail)
		list->tail = NULL;
	tmp = prev->data;
	free(prev);
	list->size--;
	return tmp;
	
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
		Node* tmp = (Node*)malloc(sizeof(Node));
		tmp = lst->head;
		for (int i = 0; i < lst->size; i++, tmp = tmp->pNext)
			printf("%d ", tmp->data);
	}
	else
		printf("Error!Size  == 0");

}
Node* GetNth(List* list, size_t index)
{
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
	if (list->size >= 1)
	{
		Node* tmp = GetNth(list, index);
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
	else
		pushFront(list, value);

}
void *delete(List* list, size_t index)
{
	if (list->size == 1 || index - 1 == list->size|| index == 0)
		popBack(list);
	Node* tmp = GetNth(list, index);
	void *value= NULL;
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
	return value;
}
int main()
{
	List *lst;
	lst = createList(&lst);
	pushFront(lst, 40);
	pushFront(lst, 50);
	pushFront(lst, 60);

	delete(lst, 1);
	delete(lst, 1);
	printList(lst);
	return 0;
}