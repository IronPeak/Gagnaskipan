#include <iostream>

using namespace std;

class IndexOutOfRangeException{};

struct IntNode
{
public:
    int data;
    IntNode* next;

    IntNode(int Data, IntNode* Next = NULL)
    {
        data = Data;
        next = Next;
    }
};

typedef IntNode* NodePtr;

class IntList
{
private:
    NodePtr head;
    NodePtr tail;
    int count;

public:
    //constant
    IntList()
    {
        head = NULL;
        tail = NULL;
        count = 0;
    }
    ~IntList()
    {
        NodePtr temp = head;
        while(temp != NULL)
        {
            head = head->next;
            delete temp;
            temp = head;
        }
        tail = NULL;
        count = 0;
    }
    //constant
    void append(int elem)
    {
        NodePtr node = new IntNode(elem);
        if(count == 0)
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }
        count++;
    }
    //linulegt
    void remove(int index)
    {
        if(0 <= index && index < count)
        {
            if(index == 0)
            {
                NodePtr temp = head;
                head = head->next;
                delete temp;
            }
            else
            {
                NodePtr temp = head;
                for(int i = 1; i < index; i++)
                {
                    temp = temp->next;
                }
                NodePtr target = temp->next;
                temp->next = temp->next->next;
                delete target;
            }
            count--;
            return;
        }
        throw IndexOutOfRangeException();
    }

    friend ostream& operator<< (ostream &out, IntList &list);
};

ostream& operator<< (ostream &out, IntList &list)
{
    NodePtr temp = list.head;
    for(int i = 0; i < list.count; i++)
    {
        out << temp->data << " ";
        temp = temp->next;
    }
    return out;
}

int main()
{
    IntList list;

    while(true)
    {
        string cmd;
        cin >> cmd;
        if(cmd == "append")
        {
            int elem;
            cin >> elem;
            list.append(elem);
        }
        if(cmd == "remove")
        {
            int index;
            cin >> index;
            list.remove(index);
        }
        cout << list << endl;
    }

    return 0;
}
