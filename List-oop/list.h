#pragma once
#include <iostream>
class List;

class Node
{
private:
    Node* pNext;
    Node* pPrev;
    List* owner;
public:
    Node* PNext();
public:
    Node();
    ~Node();
    friend class List;
};
class List
{
private:
    Node* head;
    Node* tail;
    size_t size;
public:
    List();
    ~List();
    void pushFront(Node* temp);
    void pushBack(Node* temp);
    void popFront();
    void popBack();
    Node* GetList(const size_t index);
    void insert(size_t index, Node* temp);
    void erase(const size_t index, size_t number);
    void erase(const size_t index);
    void clear();
    const size_t Size();
    Node* Remove(size_t index);
    Node* RemoveNode(Node* node);
protected:
    Node* Head();
    Node* Pnext();
};
