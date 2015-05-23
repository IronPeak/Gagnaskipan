#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>

using namespace std;

class Hash
{
private:
    double seed;
public:
    Hash(double seed)
    {
        this->seed = seed;
    }
    //Not a good hash function since it is easy to predict what the outcome is
    unsigned int GetHash(string value)
    {
        double hash = 0;
        for(unsigned int i = 0; i < value.length(); i++)
        {
            hash += value[i];
        }
        return hash; //(unsigned int)pow(hash, seed);
    }
};

class HashMapOpenAddressing
{
private:
    Hash* hash;
    string** map;
    int capacity;
    int count;

    //linulegt
    void grow()
    {
        if((double)count / (double)capacity > 0.8 || count == capacity)
        {
            int oldcapacity = capacity;
            string** oldmap = map;

            capacity = 2 * capacity;
            map = new string*[capacity];

            for(int i = 0; i < capacity; i++)
            {
                map[i] = NULL;
            }

            for(int i = 0; i < oldcapacity; i++)
            {
                if(oldmap[i] != NULL)
                {
                    Add(oldmap[i]->data());
                }
            }
        }
    }
public:
    HashMapOpenAddressing(int capacity)
    {
        count = 0;
        hash = new Hash(2);
        this->capacity = capacity;
        map = new string*[capacity];
        for(int i = 0; i < capacity; i++)
        {
            map[i] = NULL;
        }
    }
    ~HashMapOpenAddressing()
    {
        delete hash;
        for(int i = 0; i < capacity; i++)
        {
            delete map[i];
        }
        delete [] map;
    }
    //O(2n)
    void Add(string str)
    {
        grow();
        int index = hash->GetHash(str);
        cout << "Hasing " << str << " resulted in " << index << endl;
        cout << "Target index is " << index % capacity << endl;
        for(int i = index % capacity; true; i = (i+1) % capacity)
        {
            if(map[i] == NULL)
            {
                cout << "Actual index using linear probing is " << i << endl;
                map[i] = new string(str);
                count++;
                return;
            }
            if(map[i]->data() == str)
            {
                cout << "The value is already in the map" << endl;
                return;
            }
        }
    }
    //linulegt
    void Remove(string str)
    {
        int index = hash->GetHash(str);
        for(int i = index % capacity; true; i = (i+1) % capacity)
        {
            if(map[i] == NULL)
            {
                return;
            }
            if(map[i]->data() == str)
            {
                count--;
                delete map[i];
                map[i] = NULL;
                return;
            }
        }
    }
    //linulegt
    bool Contains(string str)
    {
        int index = hash->GetHash(str);
        for(int i = index % capacity; true; i = (i+1) % capacity)
        {
            if(map[i] == NULL)
            {
                return false;
            }
            if(map[i]->data() == str)
            {
                return true;
            }
        }
    }
    //linulegt
    void Print()
    {
        for(int i = 0; i < capacity; i++)
        {
            if(map[i] == NULL)
            {
                cout << "NULL" << endl;
            }
            else
            {
                cout << map[i]->data() << endl;
            }
        }
    }
};

int main()
{
    HashMapOpenAddressing map(10);
    while(true)
    {
        string cmd;
        cin >> cmd;
        system("cls");
        if(cmd == "add")
        {
            string input;
            cin >> input;
            map.Add(input);
        }
        if(cmd == "remove")
        {
            string input;
            cin >> input;
            map.Remove(input);
        }
        if(cmd == "contains")
        {
            string input;
            cin >> input;
            map.Contains(input);
        }
        map.Print();
    }

    return 0;
}
