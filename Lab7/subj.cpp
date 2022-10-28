
#include "subj.h"
#include <string>
#include <cctype>

using std::cout;
using std::cin;
using std::endl;
const static size_t  length = 4;

class FIO :public Person
{
private:
	string family, name, fatherland;
public:
	const TypeObject GetType()override;
	const int compare(const Person* rhs)const override;
	string GetCompare()const override;
	void Print()override;
	void Input()override;
};

class Email :public Person
{
private:
	string email;
public:
	const TypeObject GetType()override;
	void Input()override;
	void Print()override;
	const int compare(const Person* rhs)const override;
};

class Telephone :public Person
{
private:
	string telephone;
	string explanation;
	int check(string str)const;
public:
	const TypeObject GetType()override;
	string Get()const override;
	void Print()override;
	void Input()override;
	const int compare(const Person* rhs)const override;
};

class Data :public Person
{
private:
	int day, month, year;
	string TextNote;
public:
	const TypeObject GetType()override;

	void Input()override;
	string Get()const override;
	void Print()override;
	const int compare(const Person* rhs)const override;
};

 std::string Data::Get()const
{
	return this->TextNote;
}

int Person::GetTablenum()const
{
	return this->TableNum;
}

string Person::GetFamily()const
{
	return "";
}

string Person::Get()const
{
	return "";
}

string Person::GetCompare() const
{
	return string();
}

const int Person::compare(const Person* rhs) const
{
	return 0;
}

bool Person::operator>(const Person& person)
{
	return compare(&person);
}

bool Person::operator==(string str)
{
	const char* istr = NULL;
	int flag = 0;
	string temp;
	temp = this->Get();
	istr = temp.c_str();
	return istr && strstr(istr, str.c_str());
}


string Telephone::Get()const
{
	return explanation;
}

const TypeObject FIO::GetType()
{
	return TypeObject::isFIO;
}

const int FIO::compare(const Person* rhs) const
{
	return this->family > rhs->GetCompare() && rhs->GetCompare()!= "";
}

string FIO::GetCompare() const
{
	return this->family;
}

Person* Person::create(TypeObject type)
{
	Person* p = nullptr;
	switch (type)
	{
	case TypeObject::isFIO:
		p = new FIO;
		break;
	case TypeObject::isTelephone:
		p = new Telephone;
		break;
	case TypeObject::isEmail:
		p = new Email;
		break;
	case TypeObject::isData:
		p = new Data;
		break;
	default:
		break;
	}
	return p;
}

Person* Person::PNext()const
{
	return ((Person *)Node::PNext());
}
void SubjList::Print()const
{
	if (this)
		if (this->Head())
			for (Person *person = Head();person;person = person->PNext())
				person->Print();
		else
			printf("List is empty.\n");
	else
		printf("ERROR: wrong list!\n");
}

const int Person::Menu()
{
	int i = 0;
	cout<<"Enter a object:\n1.FIO\n2.Email\n3.Telephone\n4.Data\n";
	cin >> i;
	return i<1 || i > length ? 0 : i;
}

void FIO::Print()
{
	cout << endl;
	cout << "Person: " << family << " " << name << " " << fatherland << endl;
	cout << "TableNum: " << TableNum<<endl;
}

void FIO::Input()
{
	cout << "Enter a FIO:" << endl;
	cin >> family >> name >> fatherland;
	cout << "Enter a TableNum:" << endl;
	cin >> TableNum;
}

const TypeObject Email::GetType()
{
	return TypeObject::isEmail;
}

void Email::Input()
{
	cout << "Enter a email adress:" << endl;
	cin >> email;
	cout << "Enter a TableNum:" << TableNum << endl;
	cin >> TableNum;
}

void Email::Print()
{
	cout << "Email: " << email << endl;
	cout << "TableNum:" << TableNum << endl;
}

const int Email::compare(const Person* rhs) const
{
	return 0;
}

const TypeObject Data::GetType()
{
	return TypeObject::isData;
}

void Data::Input()
{
	cout << "Enter a data:" << endl;
	cin >> day >> month >> year;
	cout << "Enter a TextNote:" << endl;
	std::cin.ignore();
	getline(cin, TextNote);
	cout << "Enter a TableNum:"<< endl;
	cin >> TableNum;
	cout << endl;
}

void Data::Print()
{
	cout << "Data : " << day <<" day" << " " << month <<" month" << " " << year <<" year" << endl;
	cout << "TextNote: " << TextNote << endl;
	cout << "TableNum: " << TableNum << endl;
}

const int Data::compare(const Person* rhs) const
{
	return 0;
}

int Telephone::check(string str)const
{
	int count = 0;
		for (int i = 1; i <str.size(); i++)
		{
			if (isdigit(str[i]))
				count++;
			else
				break;
		}
	if (count == str.size() - 1)
		return 1;
	else
		return 0;
}


const TypeObject Telephone::GetType()
{
	return TypeObject::isTelephone;
}

void Telephone::Print()
{
	cout << "Telephone: " << telephone<<endl;
	cout << "Explanation: " << explanation << endl;
	cout << "TableNum: " << TableNum << endl;
}

void Telephone::Input()
{
	cout << "Enter a telephone:" << endl;
	cin >> telephone;
	cout << "Enter a TableNum:" << endl;
	cin >> TableNum;
	while (!check(telephone))
	{
		cout << "Error!\n" << "Enter a again telephone:" << endl;
		cin >> telephone;
	}
	cout << "Enter a explanation:" << endl;
	std::cin.ignore();
	getline(cin, explanation);
}

const int Telephone::compare(const Person* rhs) const
{
	return 0;
}

Person& SubjList::operator[](const size_t index)
{
	return *(Person *)GetList(index);
}

Person* SubjList::Head() const
{
	return (Person *)List::Head();
}

void SubjList::search(string str)
{
	SubjList& temp = *this;
	int count = 0;
	for (int i = 0;i<this->Size();i++)
	{
		if (temp[i] == str)
		{
			temp[i].Print();
			count++;
		}
	}
	if (count == 0)
		printf("Search not found nothing\n");
}

void SubjList::sortlist()
{
	SubjList* lst= new SubjList;
	int size = Size(), j = 0;
	for (int i = 0; i < size; i++)
	{
		Person* temp = (Person *)GetList(j);
		if (temp) 
		{
			if (temp->GetType() == TypeObject::isFIO)
			{
				SearchMin(temp,lst, j);
				j = 0;
			}
			else 
				j++;
		}
	}
	if (Size() > 0) 
		while (this->Head())
			lst->pushBack(Remove(0));
	Person* p = lst->Head();
	size = lst->Size();
	for (int i = 0; i < size; i++) 
		this->pushBack(lst->Remove(0));
	delete lst;
}

void SubjList::SearchMin(Person* example, SubjList* templist, int I)
{
	SubjList& L = *this;
	Person& examplet = *example;
	Person* res = nullptr, * temp = this->Head();
	int count = I, i = 0, flag = 1;
	for (i; i < this->Size(); i++)
	{
		if (examplet > L[i])
		{
			count = i;
		}
	}
	templist->pushBack(res= (Person *)this->Remove(count));
	count = 0;
	temp = this->Head();
	int j = 0, size = this->Size();
	for (; temp;)
	{
		if (temp->GetTablenum() == res->GetTablenum() 
			&& res != temp)
		{
			temp = temp->PNext();
			templist->pushBack(this->Remove(j));
		}
		else
		{
			temp = temp->PNext();
			j++;
		}

	}
}


