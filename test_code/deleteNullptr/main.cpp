#include <iostream>

using namespace std;

class DeleteNullPtr
{
public:
    DeleteNullPtr()
    {
        m_ptr = NULL;
    }

    ~DeleteNullPtr()
    {
        delete m_ptr;
    }

    void display()
    {
        cout<< "Hello It is me " << endl;
    }

 private:
    int * m_ptr;

};

void test()
{
    DeleteNullPtr d; // C++ delete NULL ptr 是安全的
    d.display();
}

int main(int argc, char *argv[])
{

    test();
    int pase = 0;


    cout << "Hello World1!" << endl;
    cin >> pase;
    cout << "Hello World2!" << endl;
    return 0;
}
