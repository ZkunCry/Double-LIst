#include <iostream>

#include "subj.h"
using namespace std;

int main()
{

	List lst;
	Person* base = new Person;
	SubjList subj;
	TypeObject type;

	type = (TypeObject)base->Menu();
	base = base->create(type);
	base->Input();
	subj.pushBack(static_cast<Node*>(base));
	subj.search("example");

}