#include <iostream>

using namespace std;

class IndexOutOfRangeException{};
class EmptyException{};

struct IntNode
{
public:
    int data;
    IntNode* left;
    IntNode* right;

    IntNode(int Data, IntNode* Left = NULL, IntNode* Right = NULL)
    {
        data = Data;
        left = Left;
        right = Right;
    }
};

typedef IntNode* NodePtr;

class IntQueue
{
private:
    NodePtr head;
    NodePtr tail;
    int count;

public:
    IntQueue()
    {
        head = NULL;
        tail = NULL;
        count = 0;
    }
    ~IntQueue()
    {
        NodePtr temp = head;
        while(temp != NULL)
        {
            head = head->right;
            delete temp;
            temp = head;
        }
        tail = NULL;
        count = 0;
    }
    //constant
    void push(int elem)
    {
        NodePtr node = new IntNode(elem);
        if(count == 0)
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->right = node;
            node->left = tail;
            tail = node;
        }
        count++;
    }
    //constant
    void pop()
    {
        if(0 < count)
        {
            NodePtr temp = head;
            head = head->right;
            delete temp;
            count--;
            return;
        }
        throw EmptyException();
    }
    //constant
    int front()
    {
        if(0 < count)
        {
            return head->data;
        }
        throw EmptyException();
    }

    friend ostream& operator<< (ostream &out, IntQueue &Queue);
};

ostream& operator<< (ostream &out, IntQueue &Queue)
{
    NodePtr temp = Queue.head;
    for(int i = 0; i < Queue.count; i++)
    {
        out << temp->data << " ";
        temp = temp->right;
    }
    return out;
}

int main()
{
    IntQueue queue;

    while(true)
    {
        string cmd;
        cin >> cmd;
        if(cmd == "push")
        {
            int elem;
            cin >> elem;
            queue.push(elem);
        }
        if(cmd == "pop")
        {
            queue.pop();
        }
        if(cmd == "front")
        {
            cout << queue.front() << " is at the front" << endl;
        }
        cout << queue << endl;
    }

    return 0;
}
