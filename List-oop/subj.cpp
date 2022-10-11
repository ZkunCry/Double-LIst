#include "subj.h"
#include <string>
#include <ctype.h>
using namespace std;
using std::cout;
using std::cin;
using std::endl;
const size_t length = 4;

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
	if (p)
		p->type = type;
	return p;
}

Person::Person()
{
	type = TypeObject::None;
}

Person::Person(TypeObject type,int tablenum)
{
	this->type = type;
	this->TableNum = tablenum;
}

void Person::Print()
{
	if (this)
	{
		switch (this->type)
		{
		case TypeObject::isFIO:
			static_cast<FIO*>(this)->Print();
			break;
		case TypeObject::isTelephone:
			static_cast<Telephone*>(this)->Print();
			break;
		case TypeObject::isEmail:
			static_cast<Email*>(this)->Print();
			break;
		case TypeObject::isData:
			static_cast<Data*>(this)->Print();
			break;
		}
	}
	else
		printf("Error!\n");
}

void SubjList::Print()
{
	if (this)
		if (this->Head())
			for (int i = 0; i < this->Size(); i++)
				static_cast<Person*>(GetList(i))->Print();
		else
			printf("List is empty.\n");
	else
		printf("ERROR: wrong list!\n");
}



int Person::Menu()
{
	int i = 0;
	cout<<"Enter a object:\n1.FIO\n2.Email\n3.Telephone\n4.Data\n";
	cin >> i;
	return i<1 || i > length ? 0 : i;
}

void Person::Input()
{
	if (this)
	{
		switch (this->type)
		{
		case TypeObject::isFIO:
			static_cast<FIO*>(this)->InputFio();
			break;
		case TypeObject::isTelephone:
			static_cast<Telephone*>(this)->InputTelephone();
			break;
		case TypeObject::isEmail:
			static_cast<Email*>(this)->InputEmail();
			break;
		case TypeObject::isData:
			static_cast<Data*>(this)->InputData();
			break;
		}
	}
	else
		printf("Error!\n");
}

TypeObject Person::GetType()
{
	return type;
}

FIO::FIO():Person()
{
	type = TypeObject::isFIO;
}

FIO::FIO(int table):Person(TypeObject::isFIO,table){}

void FIO::Print()
{
	cout << "Person: " << family << " " << name << " " << fatherland << endl;
	cout << "TableNum: " << TableNum<<endl;
}

void FIO::InputFio()
{
	cout << "Enter a FIO:" << endl;
	cin >> family >> name >> fatherland;
	cout << "Enter a TableNum:" << endl;
	cin >> TableNum;
}

Email::Email()
{
	type = TypeObject::isEmail;
}

Email::Email(int table):Person(TypeObject::isEmail,table){}

void Email::InputEmail()
{
	cout << "Enter a email adress:" << endl;
	cin >> email;
	cout << "Enter a TableNum:" << TableNum << endl;
}

void Email::Print()
{
	cout << "Email: " << email << endl;
	cout << TableNum << endl;
}

Data::Data()
{
	type = TypeObject::isData;
}

Data::Data(int table):Person(TypeObject::isData,table){}

void Data::InputData()
{
	cout << "Enter a data:" << endl;
	cin >> day >> month >> year;
	cout << "Enter a TextNote:" << endl;
	cin >> TextNote;
	cout << "Enter a TableNum:"<< endl;
	cin >> TableNum;
	cout << endl;
}

void Data::Print()
{
	cout << "Data : " << day << month << year << endl;
	cout << "TextNote: " << TextNote << endl;
	cout << "TableNum:" << TableNum << endl;
}

int Telephone::check(std::string str)
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

Telephone::Telephone()
{
	type = TypeObject::isTelephone;
}

Telephone::Telephone(int table):Person(TypeObject::isTelephone,table){}

string Telephone::GetExplanation()
{
	return explanation;
}

void Telephone::Print()
{
	cout << "Telephone: " << telephone<<endl;
	cout << "Explanation: " << explanation << endl;
	cout << "TableNum: " << TableNum << endl;
}

void Telephone::InputTelephone()
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
	cin >> explanation;
}
Node* SubjList::SearchMin(Node* example, List* templist, int I)
{
	Node* res = NULL, * temp = this->Head();
	int count = I, i = 0, flag = 1;
	for (i; i <this->Size(); i++, temp = temp->pNext) 
	{
		if (((Person*)temp)->GetType() == isFIO && compare((FIO*)example, (FIO*)temp) && ((Person*)example)->GetType() == isFIO)
		{
			count = i; 
		}
	}
	pushBack(templist, res = Remove(lst, count)); 
	count = 0;
	temp = lst->head;
	int j = 0, size = lst->size;
	for (; temp;) 
	{
		if (((Person*)temp)->TableNum == ((Person*)res)->TableNum && strcmp(((FIO*)res)->family, ((FIO*)temp)->family) != 0)
	
		{
			pushBack(templist, Remove(lst, j));
			temp = lst->head;
			j = 0; 
		}
		else
		{
			temp = temp->pNext;
			j++; 
		}

	}
	return NULL;
}

//int SubjList::compare(FIO* a, FIO* b)
//{
//	return 0;
//}
int SubjList::search_elements(Person *base,std::string str)
{
	const char* istr= NULL;
	int flag = 0;
	if (base->GetType() == TypeObject::isData)
	{
		istr = static_cast<Data*>(base)->GetTextNote().c_str();
	}
	if (base->GetType() == TypeObject::isTelephone)
	{
		istr = static_cast<Telephone*>(base)->GetExplanation().c_str();
	}
	if (istr)
		flag = 1;
	return flag;
}
std::string Data::GetTextNote()
{
	return TextNote;
}
void SubjList::search(std::string str)
{
	Person* person = static_cast<Person *>(this->Head());
	int count = 0;
	for (int i = 0;i<this->Size();i++)
	{
		if (search_elements(person = static_cast<Person*>(this->GetList(i)), str))
		{
			person->Print();
			count++;
		}
	}
	if (count == 0)
		printf("Search not found nothing\n");
}
void SubjList::sortlist()
{
	SubjList* lst= NULL;
	int size = Size(), j = 0;
	for (int i = 0; i < size; i++)
	{
		Node* temp = GetList(j); 
		if (temp) 
		{
			if ((static_cast<Person *>(temp)->GetType() == TypeObject::isFIO))
			{
				SearchMin(temp,lst, j);
				j = 0;
			}
			else 
				j++;
		}
	}
	if (Size() > 0) 
		while (Head())
			lst->pushBack(Remove(0));

	Node* p = lst->Head();
	size = lst->Size();
	for (int i = 0; i < size; i++) 
	{
		pushBack(lst->Remove(0));
	}
}


