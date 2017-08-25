#include <iostream>

using namespace std;

class TextBlock
{
public:
    TextBlock(std::string text)
    {
        m_text = text;
    }

public:
    const char& operator[](std::size_t position) const
    {return m_text[position];}

//    char operator[](std::size_t position) // 引用是引用它自己
//    {return m_text[position];}

    char& operator[](std::size_t position) // 引用是引用它自己
    {return m_text[position];}

//    const char& operator[](std::size_t position) // 引用是引用它自己
//    {return m_text[position];}

//    const char operator[](std::size_t position) // 引用是引用它自己
//    {return m_text[position];}

//    char& operator[](std::size_t position)
//    {return text[position];}

//    char& operator[](std::size_t position) const
//    {return text[position];}

private:
    std::string m_text;
};



int main(int argc, char *argv[])
{
    TextBlock tb("hello");
    std::cout << tb[0];
    tb[0] = 'x';

    const TextBlock ctb("World"); // const 对象优先调用const 函数 没有const函数，才调用非const成员函数
     std::cout << ctb[0];


    return 0;
}
