#include "BloomFilter.h"

BloomFilter::BloomFilter(int size, int hashes)
{
    this->size = size;
    this->hashes = hashes;
    filter = new bool[size];
    for(int i = 0; i < size; i++)
    {
        filter[i] = false;
    }
    collection = new HashCollection(hashes);
}

BloomFilter::~BloomFilter()
{
    delete [] filter;
    delete collection;
}

void BloomFilter::add(string s)
{
    for(int i = 0; i < hashes; i++)
    {
        int hash = collection->HashValue(s, i);
        filter[hash % size] = true;
    }
}

bool BloomFilter::contains(string s)
{
    for(int i = 0; i < hashes; i++)
    {
        int hash = collection->HashValue(s, i);
        filter[hash % size] = true;
    }
}
