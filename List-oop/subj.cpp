#include "subj.h"
#include <string>
#include <cctype>

using std::cout;
using std::cin;
using std::endl;
const static size_t  length = 4;

 std::string Data::GetTextNote()const
{
	return TextNote;
}
int Person::GetTablenum()const
{
	return this->TableNum;
}
string Telephone::GetExplanation()const
{
	return explanation;
}
TypeObject Person::GetType()const
{
	return type;
}

string FIO::GetFamily()const
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

Person::Person()
{
	type = TypeObject::None;
}

Person::Person(TypeObject type)
{
	this->type = type;
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
			for (Node *person = Head();person;person = person->PNext())
				static_cast<Person*>(person)->Print();
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
			static_cast<FIO*>(this)->Input();
			break;
		case TypeObject::isTelephone:
			static_cast<Telephone*>(this)->Input();
			break;
		case TypeObject::isEmail:
			static_cast<Email*>(this)->Input();
			break;
		case TypeObject::isData:
			static_cast<Data*>(this)->Input();
			break;
		}
	}
	else
		printf("Error!\n");
}
FIO::FIO():Person(TypeObject::isFIO){}

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

Email::Email():Person(TypeObject::isEmail){}

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

Data::Data():Person(TypeObject::isData){}

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
	cout << "Data : " << day <<" " << month <<" " << year << endl;
	cout << "TextNote: " << TextNote << endl;
	cout << "TableNum: " << TableNum << endl;
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


Telephone::Telephone():Person(TypeObject::isTelephone){}

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


int SubjList::compare(FIO* rhs,FIO* lhs)const
{
	return rhs->GetFamily() > lhs->GetFamily();
}
int SubjList::search_elements(Person *base,string str)
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

void SubjList::search(string str)
{
	Person* person = static_cast<Person *>(this->Head());
	int count = 0;
	for (int i = 0;i<this->Size();i++)
	{
		if (search_elements(person = static_cast<Person*>(person->PNext()), str))
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
	SubjList* lst= new SubjList;
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
		while (this->Head())
			lst->pushBack(Remove(0));

	Node* p = lst->Head();
	size = lst->Size();
	for (int i = 0; i < size; i++) 
	{
		this->pushBack(lst->Remove(0));
	}
}
void SubjList::SearchMin(Node* example, SubjList* templist, int I)
{
	Node* res = nullptr, * temp = this->Head();
	int count = I, i = 0, flag = 1;
	for (i; i < this->Size(); i++, temp = temp->PNext())
	{
		if (((Person*)temp)->GetType() == TypeObject::isFIO  
			&& ((Person*)example)->GetType() == TypeObject::isFIO && compare((FIO*)example, (FIO*)temp))
		{
			count = i;
		}
	}
	templist->pushBack(res = this->Remove(count));
	count = 0;
	temp = this->Head();
	int j = 0, size = this->Size();
	for (; temp;)
	{
		if ((static_cast<Person*>(temp)->GetTablenum() == static_cast<Person*>(res)->GetTablenum() 
			&& static_cast<FIO*>(res) !=static_cast<FIO *>(temp)))
		{
			templist->pushBack(this->Remove(j));
			temp = this->Head();
			j = 0;
		}
		else
		{
			temp = temp->PNext();
			j++;
		}

	}
}


