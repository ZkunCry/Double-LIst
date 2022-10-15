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
	Person();
	Person * create(TypeObject type);
	void Print();
	int Menu();
	void Input();
	TypeObject GetType()const;
	int GetTablenum()const;

};

class FIO :public Person
{
private:
	string family, name, fatherland;
public:
	string GetFamily()const;
	FIO();
	void Print();
	void Input();
};

class Email :public Person
{
private:
	string email;
public:
	Email();
	void Input();
	void Print();
};

class Telephone :public Person
{
private:
	string telephone;
	string explanation;
	int check(string str)const;
public:
	Telephone();
	string GetExplanation()const;
	void Print();
	void Input();
};

class Data :public Person
{
private:
	int day, month, year;
	string TextNote;
public:
	Data();
	void Input();
	string GetTextNote()const;
	void Print();
};

class SubjList :public List
{
public:
	void sortlist();
	void search(string str);
	void Print();
private:
	void SearchMin(Node* example, SubjList* templist, int I);
	int compare(FIO *rhs,FIO* lhs)const;
	int search_elements(Person *base,string str);
};