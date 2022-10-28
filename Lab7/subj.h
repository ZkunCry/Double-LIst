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
	virtual const TypeObject GetType()=0;
	int GetTablenum()const;
	virtual string GetFamily()const;
	virtual string Get()const;
	virtual string GetCompare()const;
	virtual const int compare(const Person* rhs)const;
	bool operator >(const Person& person);
	bool operator ==(string str);
};

class SubjList :public List
{
public:
	void sortlist();
	void search(string str);
	void Print()const;
	Person* Head()const;
private:
	void SearchMin(Person* example, SubjList* templist, int I);

	Person& operator[](const size_t index);

};