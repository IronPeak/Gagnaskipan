#include <algorithm>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Classifier
{
private:
    vector<list<string> > lists;
public:
    Classifier()
    {

    }
    void Add(string str)
    {
        if(str == "")
        {
            throw;
        }
        else
        {
            if(Contains(str) == false)
            {
                int index = tolower(str[0]) - 'a';
                lists[index].push_back(str);
            }
        }
    }
    bool Contains(string str)
    {
        int index = tolower(str[0]) - 'a';
        for(list<string>::iterator it = lists[index].begin(); it != lists[index].end(); it++)
        {
            if(*it == str)
            {
                return true;
            }
        }
        return false;
    }
    void print_letter(char c)
    {
        int index = c - 'a';
        for(list<string>::iterator it = lists[index].begin(); it != lists[index].end(); it++)
        {
            cout << *it << endl;
        }
    }
};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
