#include <iostream>
#include <vector>

using namespace std;

class Animal
{
public:
    string Name;
    void Sleep() //This is a normal function
    {
        cout << "Zzz" << endl;
    }
    virtual void Move() //This is a virtual function which mean it can be overridden in the super class
    {
        cout << "I moved forward" << endl;
    }
    virtual void Speak() = 0; //The = 0 means the function is abstract and must be defined in super class
};

class Cat : public Animal
{
public:
    Cat()
    {
        Name = "Cat";
    }
    virtual void Speak()
    {
        cout << "Meow" << endl;
    }
};

class Dog : public Animal
{
public:
    Dog()
    {
        Name = "Dog";
    }
    virtual void Speak()
    {
        cout << "Woff" << endl;
    }
};

class Crab : public Animal
{
public:
    Crab()
    {
        Name = "Crab";
    }
    virtual void Move()
    {
        cout << "I moved sideways" << endl;
    }
    virtual void Speak()
    {
        cout << "Blub" << endl;
    }
};

int main()
{
    //With inheritance you can store base classes and access the super classes through them
    vector<Animal*> zoo;

    while(true)
    {
        string cmd;
        cin >> cmd;
        if(cmd == "addcat")
        {
            Cat* c = new Cat();
            zoo.push_back(c);
        }
        if(cmd == "adddog")
        {
            Dog* d = new Dog();
            zoo.push_back(d);
        }
        if(cmd == "addcrab")
        {
            Crab* c = new Crab();
            zoo.push_back(c);
        }
        if(cmd == "sleep")
        {
            for(unsigned int i = 0; i < zoo.size(); i++)
            {
                cout << "A " << zoo[i]->Name << " in the zoo says: ";
                zoo[i]->Sleep();
            }
        }
        if(cmd == "move")
        {
            for(unsigned int i = 0; i < zoo.size(); i++)
            {
                cout << "A " << zoo[i]->Name << " in the zoo says: ";
                zoo[i]->Move();
            }
        }
        if(cmd == "speak")
        {
            for(unsigned int i = 0; i < zoo.size(); i++)
            {
                cout << "A " << zoo[i]->Name << " in the zoo says: ";
                zoo[i]->Speak();
            }
        }
    }

    return 0;
}
