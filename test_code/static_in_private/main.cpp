#include <iostream>

using namespace std;
class Session {
public:
    Session();
    ~Session();

    void display()
    {
        Session s;
        Session::logCreation(&s);
    }

private:
    static void logCreation(Session *objAddr);
    static void logDestruction(Session *objAddr);
};

void Session::logCreation(Session *objAddr)
{
    cout<< " logCreation " << endl;
}

void Session::logDestruction(Session *objAddr)
{
    cout<< " logDestruction " << endl;
    raise(1);
}

Session::Session()
{
    clog << "hello Dimon" << endl; // 也是在 cout 的一样打印到窗口中
}

Session::~Session()
{
    try {
        logDestruction(this);
    }
    catch (...) {
        cerr << "Unable to log destruction of Session object "
             << "at address "
             << this
             << ".\n";

        clog << "hello Dimon";
    }

    // cerr cout cin clog 在 iostream 中被调用
}



int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    Session s;
    s.display();
    //terminate(); // 终止程序执行
    return 0;
}
