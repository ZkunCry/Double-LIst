#pragma once
#include "list.h"

typedef enum TypeObject
{
	None,
	isFIO,
	isEmail,
	isTelephone,
	isData
}TypeObject;

typedef struct Person // Base class
{
	struct Node;
	TypeObject type;
	int TableNum;

}Person;

Person* create(TypeObject type);
void Print(Person* base);
void PrintList(List* lst);
int Menu();
void Input(Person* base);
void sortlist(List* lst);
void search(List* lst, const char* str);