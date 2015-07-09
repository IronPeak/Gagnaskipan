#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <vector>
#include <string>

using namespace std;

struct Hash
{
private:
    unsigned int seed;
public:
    Hash(unsigned int seed)
    {
        this->seed = seed;
    }

    int GetHash(string s)
    {
        int h = 0;
        for(unsigned int i = 0; i < s.length() && i < seed; i++)
        {
            h += s[i];
        }
        return h + seed * seed * 1337;
    }
};

class HashCollection
{
private:
    vector<Hash> hashes;
    int count;
public:
    HashCollection(int numberOfHashes)
    {
        count = numberOfHashes;
        for(int i = 0; i < count; i++)
        {
            hashes.push_back(Hash(i + 1));
        }
    }
    int HashValue(string element, int h)
    {
        return hashes[h].GetHash(element);
    }
    int Size()
    {
        return count;
    }
};

class BloomFilter
{
    public:
        BloomFilter(int size, int hashes);
        ~BloomFilter();
        void add(string s);
        bool contains(string s);
    private:
        bool* filter;
};

#endif // BLOOMFILTER_H
