#include <iostream>

#include "subj.h"
using namespace std;

int main()
{
	//List lst;
	//Node* temp= new Node;
	//Node* temp2 = new Node;
	//lst.pushBack(temp2);
	//lst.pushBack(temp);
	//lst.pushBack(temp);
	//lst.Print();
	Person *base= nullptr;
	SubjList subj;
	TypeObject type;
	int choose;
	string buf;
	do
	{
		printf("\nChoose the options:\n"
			"Menu:\n1.Create object\n2.Out information on display\n3.Add to the end\n"
			"4.Add to the start\n5.Delete of the end\n6.Sort list\n7.Find by given word\n0.Exit and delete object\n");
		cin >> choose;
		system("cls");
		switch (choose)
		{

		case 1:

			type = static_cast<TypeObject>(base->Menu());
			base = base->create(type);
			base->Input();
			cout << "Please choose a point 3 or 4" << endl;
			break;
		case 2:
			subj.Print();
			break;
		case 3:
			subj.pushBack(static_cast<Node *>(base));
			break;
		case 4:
			subj.pushFront(static_cast<Person *>(base));
			break;
		case 5:
			if (subj.Size())
				subj.popBack();
			break;
		case 6:
			subj.sortlist();
			break;
		case 7:
			printf("Enter a string\n");
			cin >> buf;
			subj.search(buf);
			break;
		case 0:
			break;
		}
	} while (choose != 0);
	return 0;
}