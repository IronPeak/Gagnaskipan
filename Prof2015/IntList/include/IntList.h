#ifndef INTLIST_H
#define INTLIST_H

#include<iostream>

using namespace std;

class ListException{};

struct IntNode
{
public:
    int value;
    IntNode* link;

    IntNode(int value, IntNode* link = NULL)
    {
        this->value = value;
        this->link = link;
    }
};

typedef IntNode* NodePtr;

class IntList
{
    public:
        IntList();
        ~IntList();
        void insert(unsigned int ind, int n);
        int at(unsigned int ind);
        void duplicate();
        void remove(int n);
        void reverse();
        friend ostream& operator <<(ostream& outs, const IntList& lis);
    private:
        NodePtr head;
        NodePtr tail;
        int count;

        void append(int n);
        void prepend(int n);
        void clear(NodePtr node);
};

#endif // INTLIST_H
