#pragma once
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
void pushFront(List* lst, Node* temp);
void pushBack(List* lst, Node* temp);
void popFront(List* list);
void popBack(List* lst);
void printList(List* lst);
Node* GetList(List* list, const size_t index);
void insert(List* list, const size_t index, Node* temp);
void Erase(List* list, const size_t index, size_t number);
void erase(List* list, const size_t index);
//void ReSize(List* lst, const size_t NewSize);
void clear(List** lst);
const size_t Size(List* lst);
Node* Remove(List* lst, size_t index);

