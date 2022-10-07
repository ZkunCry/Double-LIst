#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "subj.h"


int main()
{
	List lst = { NULL,NULL };
	Person* base= NULL;
	TypeObject type;
	char buf[100];
	int choose;
	do
	{
		printf("\nChoose the options:\n"
			"Menu:\n1.Create object\n2.Out information on display\n3.Add to the end\n"
			"4.Add to the start\n5.Delete of the end\n6.Sort list\n7.Find by given word\n0.Exit and delete object\n");
		scanf("%d", &choose);
		switch (choose)
		{
		case 1:
			type = Menu();
			base = create(type);
			Input(base);
			printf("Please choose a point 3 or 4\n");
			fflush(stdin);
			break;
		case 2:
			PrintList(&lst);
			break;
		case 3:
			pushBack(&lst, (Node*)base);
			break;
		case 4:
			pushFront(&lst, (Node*)base);
			break;
		case 5:
			if (lst.size)
				popBack(&lst);
			break;
		case 6:
			sortlist(&lst);
			break;
		case 7:
			printf("Enter a string\n");
			fflush(stdin);
			scanf("%s", buf);
			search(&lst,buf);
			break;
		case 0:
			clear(&lst);
			break;
		}
	} while (choose != 0);
	
	return 0;
}
