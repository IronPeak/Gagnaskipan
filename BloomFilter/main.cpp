#include <iostream>
#include <math.h>
#include <vector>

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
        return (unsigned int)pow(hash, seed);
    }
};

class HashCollection
{
private:
    vector<Hash> collection;
    int size;
public:
    HashCollection(int size)
    {
        this->size = size;
        for(int i = 0; i < size; i++)
        {
            Hash h(i);
            collection.push_back(h);
        }
    }
    ~HashCollection()
    {

    }
    int length()
    {
        return size;
    }
    unsigned int hashValue(string str, int index)
    {
        return collection[index].GetHash(str);
    }
};

class BloomFilter
{
private:
    int size;
    bool* filter;
    HashCollection* collection;
public:
    BloomFilter(int size, int hashes)
    {
        this->size = size;
        filter = new bool[size];
        collection = new HashCollection(hashes);
        for(int i = 0; i < size; i++)
        {
            filter[i] = false;
        }
    }
    ~BloomFilter()
    {
        delete [] filter;
        delete collection;
    }
    void Add(string str)
    {
        for(int i = 0; i < collection->length(); i++)
        {
            int index = collection->hashValue(str, i);
            filter[index % size] = true;
        }
    }
    bool Contains(string str)
    {
        for(int i = 0; i < collection->length(); i++)
        {
            int index = collection->hashValue(str, i);
            if(filter[index % size] == false)
            {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    BloomFilter bloom(254, 7);

    while(true)
    {
        string cmd;
        cin >> cmd;
        if(cmd == "add")
        {
            string input;
            cin >> input;
            bloom.Add(input);
            cout << "Added " << input << " to bloomfilter." << endl;
        }
        if(cmd == "contains")
        {
            string input;
            cin >> input;
            bool contains = bloom.Contains(input);
            if(contains)
            {
                cout << "It is possible" << endl;
            }
            else
            {
                cout << "Definetly not in bloomfilter" << endl;
            }
        }
    }

    return 0;
}
