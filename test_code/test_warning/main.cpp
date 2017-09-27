#include <iostream>

using namespace std;

class B
{
public:
    virtual void f() const
    {
        cout<< "hello B" << endl;
    }

};

class D : public B
{
public:
    virtual void f()
    {
        cout<< "hello D" << endl;
    }

};


int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    cout << "Hello World!" << endl;

    D d;
    d.f();


    return 0;
}
