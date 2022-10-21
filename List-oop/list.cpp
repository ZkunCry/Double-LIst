#include "list.h"
Node* Node::PNext()const
{
	return pNext;
}
Node::Node()
{
	pNext = nullptr;
	pPrev = nullptr;
	owner = nullptr;
}

Node::~Node()noexcept
{
	if (owner)
		owner->RemoveNode(this);
}
Node* List::RemoveNode(Node* node)
{
	if (node->owner == this)
	{
		for (int i = 0; i < size; i++)
		{
			if (GetList(i) == node)
				return Remove(i);		
		}
	}
	return nullptr;
}
List::List()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

List::~List()noexcept
{
	clear();
}

void List::pushFront(Node* temp)
{
	if (this && !temp->owner)
	{
		if (temp == nullptr)
			return;
		temp->owner = this;
		temp->pNext = head;
		temp->pPrev = nullptr;
		if (head)
			head->pPrev = temp;
		head = temp;
		if (tail == nullptr)
			tail = temp;
		size++;
	}
	else
		return;
}

void List::pushBack(Node* temp)
{
	if (this && !temp->owner)
	{
		if (temp == nullptr)
			return;
		temp->owner = this;
		temp->pNext = nullptr;
		temp->pPrev = tail;
		if (tail)
		{
			tail->pNext = temp;
		}
		tail = temp;
		if (head == nullptr)
			head = temp;
		size++;
	}
	else
		return;
}

void List::popFront()
{
	if (this)
	{
		if (head == nullptr)
			return;
		Node* prev;
		prev = head;
		head = head->pNext;
		if (head)
			head->pPrev = nullptr;
		if (prev == tail)
			tail = nullptr;
		prev->owner = nullptr;
		delete prev;
		size--;
	}
	else
		return;
}

void List::popBack()
{
	if (this)
	{
		if (tail == nullptr)
			return;
		Node* prev;
		prev = tail;
		tail = tail->pPrev;
		if (tail)
			tail->pNext = nullptr;
		if (prev == head)
			head = nullptr;
		prev->owner = nullptr;
		delete prev;
		size--;
	}
	else
		return;
}

Node* List::GetList(const size_t index)const
{
	if (index < size && index >= 0)
	{
		Node* tmp = nullptr;
		size_t i;
		if (index <= size / 2)
		{
			i = 0;
			tmp = head;
			while (tmp && i < index)
			{
				tmp = tmp->pNext;
				i++;
			}
		}
		else
		{
			i = size - 1;
			tmp = tail;
			while (tmp && i > index)
			{
				tmp = tmp->pPrev;
				i--;
			}
		}
		return tmp;
	}
	else
		return nullptr;
}

void List::insert(size_t index, Node* temp)
{
	if (temp->owner)
	{
		Node* tmp;
		if (index < 0)
			index = 0;
		if (tmp = GetList(index))
		{
			Node* elm = temp;
			elm->pPrev = tmp->pPrev;
			temp->owner = this;
			elm->pNext = tmp;
			tmp->pPrev = elm;
			if (!elm->pPrev)
			{
				head = elm;
			}
			else
				elm->pPrev->pNext = elm;
			if (!tmp->pNext)
				tail = tmp;
			size++;
		}
		else
		{
			temp->pNext = tail->pNext;
			temp->pPrev = tail;
			tail->pNext = temp;
			tail = temp;
			size++;
		}
	}
	else
		return;
}

void List::erase(const size_t index, size_t number)
{
	if (index < size)
	{
		if (number > size)
			number = size;
		for (int i = 0; i < number; i++)
			erase(index);
	}
}

void List::erase(const size_t index)
{
	Node* tmp = GetList(index);
	if(index < size && index >= 0)
	{
		if (tmp->pPrev)
			tmp->pPrev->pNext = tmp->pNext;
		if (tmp->pNext)
			tmp->pNext->pPrev = tmp->pPrev;
		if (!tmp->pNext)
			tail = tmp->pPrev;
		if (!tmp->pPrev)
			head = tmp->pNext;
		tmp->owner = nullptr;
		delete tmp;
		size--;
	}
}

void List::clear()
{
	if (this)
	{
		Node* tmp = head;
		Node* next = nullptr;
		while (tmp)
		{
			next = tmp->pNext;
			delete tmp;
			tmp = next;
		}
		size = 0;
		head = nullptr;
		tail = nullptr;
	}
}

const size_t List::Size()const
{
	return size;
}

Node* List::Remove(size_t index)
{
	if (index < size && index >= 0)
	{
		Node* tmp = GetList(index);
		if (tmp->pPrev)
			tmp->pPrev->pNext = tmp->pNext;
		if (tmp->pNext)
			tmp->pNext->pPrev = tmp->pPrev;
		if (!tmp->pNext)
			tail = tmp->pPrev;
		if (!tmp->pPrev)
			head = tmp->pNext;
		tmp->owner = nullptr;
		size--;
		return tmp;
	}
	else
		return nullptr;
}
void List::Print()
{
	std::cout << "Item: " << this << "\t"
		<< "head: " << head << "\t"
		<< "tail: " << tail << std::endl;

	Node* p = head;
	for (int i = 0; p; i++, p = p->pNext)
		printf("%d\t%p\t%p\t%p;\n", i, p, p->pPrev, p->pNext);
}

Node* List::Head()const 
{
	return head;
}