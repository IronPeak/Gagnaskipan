#include <iostream>
#include "Map.h"

using namespace std;

int main()
{
    Map tree;
    string cmd;
    while(cmd != "quit")
    {
        cin >> cmd;
        if(cmd == "add")
        {
            string key;
            int value;
            cout << "Key: ";
            cin >> key;
            cout << "Value: ";
            cin >> value;
            tree.add(key, value);
        }
        if(cmd == "removemax")
        {
            tree.remove_max();
        }
        if(cmd == "print")
        {
            int n;
            cin >> n;
            tree.print_by_values(n);
        }
        tree.print();
    }
    return 0;
}
