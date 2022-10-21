#pragma once
#include "list.h"

using std::string;

enum class TypeObject
{
	None,
	isFIO,
	isEmail,
	isTelephone,
	isData
};

class Person :public Node
{
protected:
	TypeObject type;
	size_t TableNum;
	Person(TypeObject type);
public:
	static Person * create(TypeObject type);
	void Print();
	const int Menu();
	void Input();
	TypeObject GetType()const;
	int GetTablenum()const;
};



class SubjList :public List
{
public:
	void sortlist();
	void search(string str)const;
	void Print()const;
private:
	void SearchMin(Node* example, SubjList* templist, int I);
	const int compare(Person *rhs,Person* lhs)const;
	int search_elements(Person *base,string str)const;
};