#include "pqueue.h"

pqueue::pqueue()
{
    first = NULL;
}

pqueue::~pqueue()
{
    while(first != NULL)
    {
        NodePtr temp = first;
        first = first->link;
        delete temp;
    }
}

void pqueue::enqueue(string element, int n)
{
    if(first == NULL || first->priority < n)
    {
        first = new Node(element, n, first);
        return;
    }
    else
    {
        NodePtr temp = first;
        while(temp->link != NULL && temp->link->priority > n)
        {
            temp = temp->link;
        }
        NodePtr node = new Node(element, n, temp->link);
        temp->link = node;
    }
}

string pqueue::dequeue()
{
    if(first == NULL)
    {
        throw;
    }
    string str = first->value;
    NodePtr temp = first;
    first = first->link;
    delete temp;
    return str;
}

void pqueue::print()
{
    NodePtr temp = first;
    while(temp != NULL)
    {
        cout << temp->priority << " ";
        temp = temp->link;
    }
}
