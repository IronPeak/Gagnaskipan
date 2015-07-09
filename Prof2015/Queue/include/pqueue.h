#ifndef PQUEUE_H
#define PQUEUE_H

#include <string>

using namespace std;

struct Node
{
    int priority;
    string value;
    Node* link;
    Node(string value, int priority, Node* link = NULL)
    {
        this->value = value;
        this->priority = priority;
        this->link = link;
    }
};

typedef Node* NodePtr;

class pqueue
{
    public:
        pqueue();
        ~pqueue();
        void enqueue(string element, int n);
        string dequeue();
    private:
        NodePtr first;
};

#endif // PQUEUE_H
