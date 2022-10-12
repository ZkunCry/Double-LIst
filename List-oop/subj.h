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
public:
	int GetTablenum();
	Person * create(TypeObject type);
	Person();
	Person(TypeObject type, int tablenum);
	void Print();
	int Menu();
	void Input();
	TypeObject GetType();
};

class FIO :public Person
{
private:
	string family, name, fatherland;
public:
	string GetFamily();
	FIO();
	FIO(int table);
	void Print();
	void InputFio();
};

class Email :public Person
{
private:
	string email;
public:
	Email();
	Email(int table);
	void InputEmail();
	void Print();
};

class Telephone :public Person
{
private:
	string telephone;
	string explanation;
	int check(std::string str);
public:
	Telephone();
	Telephone(int table);
	string GetExplanation();
	void Print();
	void InputTelephone();
};

class Data :public Person
{
private:
	int day, month, year;
	string TextNote;
public:
	Data();
	Data(int table);
	void InputData();
	std::string GetTextNote();
	void Print();
};

class SubjList :public List
{
public:
	void sortlist();
	void search(std::string str);
	void Print();
private:
	void SearchMin(Node* example, SubjList* templist, int I);
	int compare(FIO *rhs,FIO* lhs);
	int search_elements(Person *base,std::string str);
};