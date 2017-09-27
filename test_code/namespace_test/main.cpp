#include <iostream>

using namespace std;

void outOfMem()
{
    std::cerr << "Unable to satisfy request for memory\n";
    std::abort();
}

int main(int argc, char *argv[])
{
    std::set_new_handler(outOfMem);
    int * pBigDataArray = new int[10000000L];
    cout << "Hello World!" << endl;
    return 0;
}
