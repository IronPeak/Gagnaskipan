#include <iostream>
#include "pqueue.h"

using namespace std;

int main()
{
    string cmd;
    pqueue queue;
    while(cmd != "quit")
    {
        cin >> cmd;
        if(cmd == "add")
        {
            int n;
            cin >> n;
            queue.enqueue("a", n);
        }
        queue.print();
    }
    return 0;
}
