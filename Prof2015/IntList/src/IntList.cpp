#include "IntList.h"

IntList::IntList()
{
    count = 0;
    head = NULL;
    tail = NULL;
}

IntList::~IntList()
{
    clear(head);
}

void IntList::clear(NodePtr node)
{
    while(node != NULL)
    {
        NodePtr temp = node;
        node = node->link;
        delete temp;
    }
}

//O(n) eğa Linear
void IntList::insert(unsigned int ind, int n)
{
    if(count < ind)
    {
        throw ListException();
    }
    else
    {
        if(ind == count)
        {
            append(n);
        }
        else if(ind == 0)
        {
            NodePtr node = new IntNode(n);
            node->link = head;
            head = node;
            count++;
        }
        else
        {
            NodePtr target = head;
            for(unsigned int i = 1; i < ind; i++)
            {
                target = target->link;
            }
            NodePtr node = new IntNode(n, target->link);
            target->link = node;
            count++;
        }
    }
}

void IntList::append(int n)
{
    NodePtr node = new IntNode(n);
    if(count == 0)
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->link = node;
        tail = node;
    }
    count++;
}

//Linear eğa O(n)
int IntList::at(unsigned int ind)
{
    if(count < ind)
    {
        throw ListException();
    }
    else
    {
        NodePtr target = head;
        for(unsigned int i = 1; i < ind; i++)
        {
            target = target->link;
        }
        return target->value;
    }
}

void IntList::duplicate()
{
    int length = count;
    NodePtr target = head;
    for(unsigned int i = 0; i < length; i++)
    {
        insert(2 * i, target->value);
        target = target->link;
    }
}

void IntList::remove(int n)
{
    while(head != NULL && head->value == n)
    {
        NodePtr temp = head;
        head = head->link;
        delete temp;
        count--;
    }
    NodePtr target = head;
    while(target != NULL)
    {
        if(target->link != NULL)
        {
            if(target->link->value == n)
            {
                NodePtr temp = target->link;
                target->link = temp->link;
                delete temp;
                count--;
            }
            else
            {
                target = target->link;
            }
        }
        else
        {
            tail = target;
            break;
        }
    }
}

void IntList::reverse()
{
    count = 0;
    NodePtr oldHead = head;
    head = tail = NULL;
    NodePtr temp = oldHead;
    while(temp != NULL)
    {
        prepend(temp->value);
        temp = temp->link;
    }
    clear(oldHead);
}

void IntList::prepend(int n)
{
    NodePtr node = new IntNode(n);
    if(count == 0)
    {
        head = node;
        tail = node;
    }
    else
    {
        node->link = head;
        head = node;
    }
    count++;
}

ostream& operator <<(ostream& outs, const IntList& lis)
{
    NodePtr temp = lis.head;
    while(temp != NULL)
    {
        outs << temp->value << " ";
        temp = temp->link;
    }
    return outs;
}
