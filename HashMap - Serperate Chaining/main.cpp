#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>

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

class HashMapSeperateChaining
{
private:
    Hash* hash;
    vector<string>** map;
    int capacity;
    int count;

    //linulegt
    void grow()
    {
        if((double)count / (double)capacity > 2 || count == capacity)
        {
            int oldcapacity = capacity;
            vector<string>** oldmap = map;

            capacity = 2 * capacity;
            map = new vector<string>*[capacity];

            for(int i = 0; i < capacity; i++)
            {
                map[i] = NULL;
            }

            for(int i = 0; i < oldcapacity; i++)
            {
                if(oldmap[i] != NULL)
                {
                    for(unsigned int j = 0; j < oldmap[i]->size(); j++)
                    {
                        Add(oldmap[i]->at(j).data());
                    }
                }
            }
        }
    }
public:
    HashMapSeperateChaining(int capacity)
    {
        count = 0;
        hash = new Hash(2);
        this->capacity = capacity;
        map = new vector<string>*[capacity];
        for(int i = 0; i < capacity; i++)
        {
            map[i] = NULL;
        }
    }
    ~HashMapSeperateChaining()
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
        index = index % capacity;
        if(map[index] == NULL)
        {
            map[index] = new vector<string>();
        }
        else
        {
            for(unsigned int i = 0; i < map[index]->size(); i++)
            {
                if(map[index]->at(i) == str)
                {
                    cout << "This value is already in the map" << endl;
                    return;
                }
            }
        }
        map[index]->push_back(str);
        count++;
        return;
    }
    //linulegt
    void Remove(string str)
    {
        int index = hash->GetHash(str);
        index = index % capacity;
        if(map[index] == NULL)
        {
            return;
        }
        else
        {
            for(unsigned int i = 0; i < map[index]->size(); i++)
            {
                if(map[index]->at(i) == str)
                {
                    map[index]->erase (map[index]->begin()+i);
                    count--;
                    return;
                }
            }
        }
    }
    //linulegt
    bool Contains(string str)
    {
        int index = hash->GetHash(str);
        index = index % capacity;
        if(map[index] == NULL)
        {
            return false;
        }
        else
        {
            for(unsigned int i = 0; i < map[index]->size(); i++)
            {
                if(map[index]->at(i) == str)
                {
                    return true;
                }
            }
            return false;
        }
    }
    //linulegt
    void Print()
    {
        for(int i = 0; i < capacity; i++)
        {
            cout << i << " ";
            if(map[i] == NULL)
            {
                cout << "NULL" << endl;
            }
            else
            {
                for(unsigned int j = 0; j < map[i]->size(); j++)
                {
                    cout << map[i]->at(j) << " ";
                    if(j < map[i]->size() - 1)
                    {
                        cout << "-> ";
                    }
                }
                cout << endl;
            }
        }
    }
};

int main()
{
    HashMapSeperateChaining map(10);
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
