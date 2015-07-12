#include <iostream>

using namespace std;

class A
{
public:
    A()
    {
        cout << "A empty constructor" << endl;
    }
    A(int value)
    {
        cout << "A int constructor" << endl;
    }
};

class B : public A
{
public:
    B(int value) : A(1)
    {
        cout << "B int constructor" << endl;
    }
    ~
};

int main()
{
    B* b = new B(1);
    return 0;
}
