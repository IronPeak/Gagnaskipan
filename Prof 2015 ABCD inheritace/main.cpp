#include <iostream>

using namespace std;

class A
{
protected:
    int a, b;
public:
    A() : a(10), b(20) {};
    virtual int fun() = 0;
};

class B : public A
{
public:
    int fun()
    {
        return a;
    }
    int fun2()
    {
        return 5;
    }
};

class C : public B
{
public:
    int fun()
    {
        return b;
    }
    int fun2()
    {
        return 15;
    }
};

class D : public A
{
public:
    int fun2()
    {
        return 17;
    }
};

int main()
{
    B* b = new C();
    cout << b->fun2();
    return 0;
}
