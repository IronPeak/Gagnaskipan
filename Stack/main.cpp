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

class IntStack
{
private:
    NodePtr head;
    NodePtr tail;
    int count;

public:
    IntStack()
    {
        head = NULL;
        tail = NULL;
        count = 0;
    }
    ~IntStack()
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
            node->right = head;
            head->left = node;
            head = node;
        }
        count++;
    }
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
    int top()
    {
        if(0 < count)
        {
            return head->data;
        }
        throw EmptyException();
    }

    friend ostream& operator<< (ostream &out, IntStack &stack);
};

ostream& operator<< (ostream &out, IntStack &stack)
{
    NodePtr temp = stack.head;
    for(int i = 0; i < stack.count; i++)
    {
        out << temp->data << " ";
        temp = temp->right;
    }
    return out;
}

int main()
{
    IntStack stack;

    while(true)
    {
        string cmd;
        cin >> cmd;
        if(cmd == "push")
        {
            int elem;
            cin >> elem;
            stack.push(elem);
        }
        if(cmd == "pop")
        {
            stack.pop();
        }
        if(cmd == "top")
        {
            cout << stack.top() << " is at the top" << endl;
        }
        cout << stack << endl;
    }

    return 0;
}
