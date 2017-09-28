#include <iostream>
#include <new>

using namespace std;

class Widget
{
public:
    static void* operator new(std::size_t size,std::ostream& logStream) throw(std::bad_alloc);
    // 非正常形式的new
    static void operator delete(void* pMemory, std::size_t size) throw();
    // 正常的 class专属 delete

    void* operator new(std::size_t,void* pMenory) throw();
    // placement new
private:

};

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    return 0;
}
