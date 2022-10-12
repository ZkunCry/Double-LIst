#pragma once
#include "list.h"

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
	int TableNum;
public:
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
	std::string family, name, fatherland;
public:
	FIO();
	FIO(int table);
	void Print();
	void InputFio();
};

class Email :public Person
{
private:
	std::string email;
public:
	Email();
	Email(int table);
	void InputEmail();
	void Print();
};

class Telephone :public Person
{
private:
	std::string telephone;
	std::string explanation;
	int check(std::string str);
public:
	Telephone();
	Telephone(int table);
	std::string GetExplanation();
	void Print();
	void InputTelephone();
};

class Data :public Person
{
private:
	int day, month, year;
	std::string TextNote;
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
	Node* SearchMin(Node* example, List* templist, int I);
	int compare(FIO* a, FIO* b);
	int search_elements(Person *base,std::string str);
};