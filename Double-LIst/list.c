#include "list.h"
List* createList()
{
	List* tmp = (List*)malloc(sizeof(List));
	tmp->size = 0;
	tmp->head = tmp->tail = NULL;
	return tmp;
}
void pushFront(List* lst, Node* temp)
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
		return;
}
void pushBack(List* lst, Node* temp)
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
		return;
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
		return;
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
		return;
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
		return NULL;
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
		return NULL;
}

void insert(List* list,size_t index, Node* temp)
{
	Node* tmp; 
	if (index < 0)
		index = 0;
	if (tmp = GetList(list, index))
	{
		Node* elm = temp;
		elm->pPrev = tmp->pPrev;
		elm->pNext = tmp;
		tmp->pPrev = elm;
		if (!elm->pPrev)
		{
			list->head = elm;
		}
		else
			elm->pPrev->pNext = elm;
		if (!tmp->pNext)
			list->tail = tmp;
		list->size++;
	}
	else
	{
		temp->pNext = list->tail->pNext;
		temp->pPrev = list->tail;
		list->tail->pNext = temp;
		list->tail = temp;
		list->size++;
	}
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

void clear(List* lst)
{
	if (lst)
	{
		Node* tmp = lst->head;
		Node* next = NULL;
		while (tmp)
		{
			next = tmp->pNext;
			free(tmp);
			tmp = next;
		}
		lst->size = 0;
		lst = NULL;
	}
}