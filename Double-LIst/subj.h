#pragma once
#include "list.h"
typedef enum TypeObject
{
	None,
	Person
}TypeObject;

typedef struct Person
{
	struct Node;
	char family[30];
	char name[30];
	char fatherland[30];
}Person;
typedef struct Data
{
	struct Person;
	char* telephone;
	char* email;
	char* NumTable;

}DataPerson;

typedef struct SubjList
{
	struct DbList;

}SubjList;

