#include <iostream>
#include <IntList.h>

using namespace std;

int main()
{
    IntList listi;
    string cmd;
    while(cmd != "quit")
    {
        cin >> cmd;
        if(cmd == "add")
        {
            int i;
            cin >> i;
            int n;
            cin >> n;
            listi.insert(i, n);
        }
        if(cmd == "at")
        {
            int n;
            cin >> n;
            cout << "result: " << listi.at(n) << endl;
        }
        if(cmd == "duplicate")
        {
            listi.duplicate();
        }
        if(cmd == "remove")
        {
            int n;
            cin >> n;
            listi.remove(n);
        }
        if(cmd == "reverse")
        {
            listi.reverse();
        }
        cout << listi << endl;
    }
    return 0;
}
