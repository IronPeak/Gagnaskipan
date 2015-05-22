#include <iostream>

using namespace std;

class IndexOutOfRangeException{};
class EmptyException{};

class IntVector
{
private:
    int* array;
    int count;
    int capacity;

    void grow()
    {
        cout << "The vector exceeded it's capacity so we have to double it's size" << endl;
        capacity += capacity;
        int* oldarray = array;
        array = new int[capacity];
        for(int i = 0; i < count; i++)
        {
            array[i] = oldarray[i];
        }
        delete [] oldarray;
    }

    void swap(int& a, int& b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

public:
    IntVector()
    {
        array = NULL;
        count = 0;
        capacity = 1;
        array = new int[capacity];
    }
    ~IntVector()
    {
        delete [] array;
        count = 0;
        capacity = 0;
    }
    void push_back(int elem)
    {
        if(count == capacity)
        {
            grow();
        }
        array[count] = elem;
        count++;
    }
    void pop_back()
    {
        if(0 < count)
        {
            count--;
            return;
        }
        throw EmptyException();
    }
    void remove(int index)
    {
        if(0 <= index && index < count)
        {
            for(int i = index; i < count; i++)
            {
                swap(array[i], array[i + 1]);
            }
            count--;
            return;
        }
        throw IndexOutOfRangeException();
    }
    int& operator[](int index)
    {
        if(0 <= index && index < count)
        {
            return array[index];
        }
        throw IndexOutOfRangeException();
    }

    friend ostream& operator<< (ostream &out, IntVector &Vec);
};

ostream& operator<< (ostream &out, IntVector &Vec)
{
    for(int i = 0; i < Vec.count; i++)
    {
        out << Vec[i] << " ";
    }
    return out;
}

int main()
{
    IntVector vec;

    while(true)
    {
        string cmd;
        cin >> cmd;
        if(cmd == "add")
        {
            int elem;
            cin >> elem;
            vec.push_back(elem);
        }
        if(cmd == "remove")
        {
            int index;
            cin >> index;
            vec.remove(index);
        }
        if(cmd == "get")
        {
            int index;
            cin >> index;
            cout << vec[index] << endl;
        }
        if(cmd == "pop")
        {
            vec.pop_back();
        }
        cout << vec << endl;
    }

    return 0;
}
