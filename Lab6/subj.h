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
	size_t TableNum;
public:
	static Person * create(TypeObject type);
	Person* PNext()const;
	virtual void Print()=0;
	static const int Menu();
	virtual void Input()=0;
	virtual TypeObject GetType()=0;
	int GetTablenum()const;
	virtual string GetFamily()const;
	virtual string GetExplanation()const;
	virtual string GetTextNote()const;
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