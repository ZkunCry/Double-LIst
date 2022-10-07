#define  _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <ctype.h>
#include "subj.h"
const size_t length = 4;

typedef struct FIO // inherited class
{
	struct Person;
	char family[30];
	char name[30];
	char fatheland[30];

}FIO;
typedef struct Email // inherited class
{
	struct Person;
	char email[255];

}Email;
typedef struct Telephone // inherited class
{
	struct Person;
	char telephone[20];
	char explanation[100];

}Telephone;
typedef struct Data // inherited class
{
	struct Person;
	int day;
	int month;
	int year;
	char TextNote[80];

}Data;

void PrintFio(FIO* p);
void PrintTelephone(Telephone* p);
void PrintEmail(Email* p);
void PrintData(Data* p);
int check(char* str);
void InputFio(FIO* p);
void InputEmail(Email* p);
void InputTelephone(Telephone* p);
void InputData(Data* data);

Person* create(TypeObject type) // "Constructor" for classes
{
	Person* p = NULL;
	switch (type)
	{
	case isFIO:
		p = malloc(sizeof(FIO));
		break;
	case isTelephone:
		p = malloc(sizeof(Telephone));
		break;
	case isEmail:
		p = malloc(sizeof(Email));
		break;
	case isData:
		p= malloc(sizeof(Data));
		break;
	default:
		break;
	}
	if (p)
		p->type = type;
	return p;
}
void Input(Person* base)
{
	switch (base->type)
	{
	case isFIO:
		InputFio((FIO*)base);
		break;
	case isTelephone:
		InputTelephone((Telephone*)base);
		break;
	case isEmail:
		InputEmail((Email*)base);
		break;
	case isData:
		InputData((Data*)base);
		break;
	default:
		break;
	}
}
int Menu()
{
	int i = 0;
	printf("\nEnter a object:\n1.FIO\n2.Email\n3.Telephone\n4.Data\n");
	fflush(stdin);
	scanf("%d", &i);
	return i<1 || i > length ? 0 : i;
}
void Print(Person* base)
{
	if (base)
	{
		switch (base->type)
		{
		case isFIO:
			PrintFio((FIO*)base);
			break;
		case isTelephone:
			PrintTelephone((Telephone*)base);
			break;
		case isEmail:
			PrintEmail((Email*)base);
			break;
		case isData:
			PrintData((Data*)base);
			break;
		}
	}
	else
		printf("Error!\n");
}
void InputFio(FIO* p)
{
	printf("Enter a FIO:\n");
	scanf("%s %s %s", p->family, p->name, p->fatheland);
	printf("Enter a TableNum:\n");
	scanf("%d", &p->TableNum);
}
void InputTelephone(Telephone* p)
{
	printf("Enter a telephone:\n");
	scanf("%s", p->telephone);
	printf("Enter a TableNum:\n");
	scanf("%d",&p->TableNum);
	while (!check(p->telephone))
	{
		printf("Error!\n Enter a again telephone:\n");
		scanf("%s", p->telephone);
	}
	getchar();
	printf("Enter a expalantion:\n");
	fgets(p->explanation, 100, stdin);

}
int check(char* str)
{
	int count = 0;
	if (str || *str)
	{
		for (int i = 1; i < strlen(str); i++)
		{
			if (isdigit(str[i]))
				count++;
			else
				break;
		}
	}
	if (count == strlen(str)-1)
		return 1;
	else
		return 0;
}
void InputEmail(Email* p)
{
	printf("Enter a email adress:\n");
	getchar();
	fgets(p->email, 255, stdin);
	printf("Enter a TableNum:\n");
	scanf("%d", &p->TableNum);
}
void InputData(Data* data)
{
	printf("Enter a data:\n");
	scanf("%d%d%d", &data->day, &data->month, &data->year);
	getchar();
	printf("Enter a textNote:\n");
	fflush(stdin);
	fgets(data->TextNote, 80, stdin);
	printf("Enter a TableNum:\n");
	scanf("%d", &data->TableNum);

}
void PrintList(List* lst)
{
	Node* p;
	if (lst)
		if (lst->head)
			for (p = lst->head; p; p = p->pNext)
				Print((Person*)p);
		else
			printf("List is empty.\n");
	else
		printf("ERROR: wrong list!\n");
}
void PrintFio(FIO *p)
{
	printf("Person: %s %s %s \n", p->family, p->name, p->fatheland);
	printf("TableNum: %d \n", p->TableNum);
}
void PrintTelephone(Telephone* p)
{
	printf("Telephone: %s\nExplanation: %s\n", p->telephone,p->explanation);
	printf("TableNum: %d \n", p->TableNum);
}
void PrintEmail(Email* p)
{
	printf("Email: %s \n", p->email);
	printf("TableNum: %d \n", p->TableNum);
}
void PrintData(Data* p)
{
	printf("Data: %d.%d.%d TextNote: %s \n", p->day, p->month, p->year, p->TextNote);
	printf("TableNum: %d ", p->TableNum);
}
int compare(FIO* a, FIO* b)
{
	return strcmp(a->family,b->family)>0;
}
int search_elements(Person* person, const char* str)
{
	char* istr= NULL;
	int flag = 0;
	if (person->type == isData)
	{
		istr = strstr(((Data*)person)->TextNote, str);
	}
	else if (person->type == isTelephone)
	{
		istr = strstr(((Telephone*)person)->explanation, str);
	}
	if (istr)
		flag = 1;
	return flag;
}
void search(List* lst, const char* str)
{
	Person* person = lst->head;
	int count = 0;
	for (person; person; person = person->pNext)
	{
		if (search_elements(person, str))
		{
			Print(person);
			count++;
		}
	}
	if (count == 0)
		printf("Search not found nothing\n");
}
Node* SearchMin(List* lst, Node* example,List *templist,int I)
{
	Node* res = NULL, *temp = lst->head;
	int count = I,i=0,flag=1;
	for (i; i < lst->size; i++, temp = temp->pNext) /* ����, ������� ���������� � ������ ������ � ���� ��� ���� ������� 
													������ FIO, ���� �� �������, �� ������������ � �������� ������� 
													�� �������� � �������*/
	{
		if (((Person*)temp)->type == isFIO && ((Person*)example)->type == isFIO && compare((FIO*)example, (FIO*)temp))
			count = i; //���� ���������� ��� ��� ����� ������� ������ �������, �� �� ���������� ������ �������
	}
	pushBack(templist,res =Remove(lst,count)); //����� �������� � ������, �� ��� ���� ���� �� ������ ������� ��� �� ��������� ������!
	count = 0;
	temp = lst->head;
	int j = 0,size=lst->size;
	for (;temp;) /*���� ��� ������ ��������� � ����� �� ��������� �������*/
	{
		if (((Person*)temp)->TableNum == ((Person*)res)->TableNum && strcmp(((FIO*)res)->family,((FIO*)temp)->family) !=0) 
			/*���� ��������� ������ ���� ��������� ����� � ��� ���� ������ ������� �� �������� ����� �����, ��������
			���� temp->family = "Aksentev" � ���� res->family = temp->family , �� ������ ������� � ������ ��� �� ��������� ������*/
		{
			pushBack(templist, Remove(lst,j));
			temp = lst->head;
			j=0; //�������� � ���� � ������ ������ �����
		}
		else
		{
			temp = temp->pNext;
			j++; //����� �������������� � ���� ������
		}

	}
}
void  sortlist(List* lst)
{
	List* templist = createList(); //������� ��������� ������ � ������� ����� ���������� ��� ��������������� ��������
	int size = lst->size,j = 0;
	for (int i = 0;i <size; i++)
	{
		Node* temp = GetList(lst, j); //���� � ������ ������ ���� FIO
		if (temp) //���� temp ������ �� 0, �� �������� ������, ������ ������ �� ����������
		{
			if (((Person*)temp)->type == isFIO) // ���� ������ ������ FIO, �� ������� � ������� ����������
			{
				SearchMin(lst, temp, templist, j);
				j = 0;
			}
			else // ����� �������� ������ ���� �� ���������� ������
				j++;
		}
	}
	if (lst->size > 0) /*���� ���������� ���, ��� ������� �������� � ������� ��������� ������ �� ��������� � ������� ����������
					   , �� �� ���� ������ ������ �� NULL ������ �������� � ��������� ������*/
		while (lst->head)
			pushBack(templist, Remove(lst, 0));

	Node* p = templist->head;
	size = templist->size;
	for (int i = 0; i < size; i++) /*����� ������ �������� �� ���������� ������ �������� � ��������
								   ����������: �������� ������ � ������� �� �����! ��� ��� � ������� ������� ����������� ������,
								   � �� ��������� �� ������! */
	{
		pushBack(lst, Remove(templist,0));
	}
}
