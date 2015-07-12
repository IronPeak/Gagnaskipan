#include <iostream>

using namespace std;

class CustomIntVector
{
private:
    int count;
    int* array;
    int capacity;
    int highestValue;

    void grow()
    {
        if(count == capacity)
        {
            capacity += capacity;
            int* oldarray = array;
            array = new int[capacity];
            for(int i = 0; i < count; i++)
            {
                array[i] = oldarray[i];
            }
            delete [] oldarray;
        }
    }

    void push_back(int value)
    {
        grow();
        array[count] = value;
        count++;
    }

    void insert(int index, int value)
    {
        push_back(value);
        for(int i = count - 1; index < i; i--)
        {
            swap(array[i-1], array[i]);
        }
    }

    void swap(int& a, int& b)
    {
        int t;
        t = a;
        a = b;
        b = t;
    }

    bool contains(int* array, int count, int value)
    {
        for(int i = 0; i < count; i++)
        {
            cout << array[i] << " ";
        }
        cout << endl;
        if(count == 0)
        {
            return false;
        }
        if(count % 2 == 0)
        {
            int index = (count / 2) - 1;
            if(value < array[index])
            {
                return contains(array, index, value);
            }
            if(value > array[index])
            {
                return contains(&array[index + 1], index + 1, value);
            }
            return true;
        }
        else
        {
            int index = count / 2;
            if(value < array[index])
            {
                return contains(array, index, value);
            }
            if(value > array[index])
            {
                return contains(&array[index + 1], index, value);
            }
            return true;
        }
    }

public:
    CustomIntVector()
    {
        count = 0;
        capacity = 1;
        array = new int[1];
        highestValue = 0;
    }

    ~CustomIntVector()
    {
        delete [] array;
    }

    void add(int value)
    {
        if(highestValue < value)
        {
            highestValue = value;
            push_back(value);
        }
        else
        {
            for(int i = 0; i < count; i++)
            {
                if(value < array[i])
                {
                    insert(i, value);
                    return;
                }
            }
        }
    }

    bool contains(int value)
    {
        return contains(array, count, value);
    }

    void print()
    {
        for(int i = 0; i < count; i++)
        {
            cout << array[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    CustomIntVector vector;
    string cmd;
    while(cmd != "quit")
    {
        cin >> cmd;
        if(cmd == "add")
        {
            int n;
            cin >> n;
            vector.add(n);
        }
        if(cmd == "contains")
        {
            int n;
            cin >> n;
            cout << (vector.contains(n) ? "true" : "false") << endl;
        }
        vector.print();
    }
    return 0;
}
