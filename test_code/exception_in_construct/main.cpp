#include <iostream>

using namespace std;

class Image { // 用于图像数据
public:
    Image(const string& imageDataFileName);

};

class AudioClip { // 用于声音数据
public:
    AudioClip(const string& audioDataFileName);

};

class PhoneNumber {  }; // 用于存储电话号码


//class BookEntry { // 通讯录中的条目
//public:
//    BookEntry(const string& name,
//              const string& address = "",
//              const string& imageFileName = "",
//              const string& audioClipFileName = "");

//    ~BookEntry();
//    // 通过这个函数加入电话号码
//    void addPhoneNumber(const PhoneNumber& number);

//private:
//    string theName; // 人的姓名
//    string theAddress; // 他们的地址
//    list<PhoneNumber> thePhones; // 他的电话号码
//    Image *theImage; // 他们的图像
//    AudioClip *theAudioClip; // 他们的一段声音片段
//};

//BookEntry::BookEntry(const string &name, const string &address, const string &imageFileName, const string &audioClipFileName)
//    : theName(name)
//    , theAddress(address)
//{

//    try
//    {
//        if(imageFileName != "")
//        {
//            theImage = new Image(imageFileName);
//        }
//        if(audioClipFileName  != "" )
//        {
//            theAudioClip = new AudioClip(audioClipFileName);
//        }
//    }
//    catch(...)
//    {
//        delete theImage;
//        delete theAudioClip;
//        throw;
//    }

//}

//class BookEntry { // 通讯录中的条目
//public:
//    BookEntry(const string& name,
//              const string& address = "",
//              const string& imageFileName = "",
//              const string& audioClipFileName = "");

//    ~BookEntry();
//    // 通过这个函数加入电话号码
//    void addPhoneNumber(const PhoneNumber& number);

//private:
//    string theName; // 人的姓名
//    string theAddress; // 他们的地址
//    list<PhoneNumber> thePhones; // 他的电话号码
//    Image * const theImage; // 他们的图像
//    AudioClip * const theAudioClip; // 他们的一段声音片段
//};

//BookEntry::BookEntry(const string &name, const string &address, const string &imageFileName, const string &audioClipFileName)
//    : theName(name)
//    , theAddress(address)
//    , theImage( imageFileName != "" ? new Image(imageFileName) : NULL)
//    , theAudioClip( audioClipFileName != "" ? new AudioClip(audioClipFileName) : NULL )
//{


//}

void sentAException()
{
    throw 1.1;
}

void functionAbouException() throw(int)
{

    cout << "the exception reguler is in" <<endl;
    try
    {
        sentAException();
    }
    catch(int& exception)
    {
        if(exception  == 1)
        {
            cout << "this exception is int number: "<< exception << endl;
        }
    }

    catch(...)
    {
        cout << "other exception" << endl;
    }
}

int main(int argc, char *argv[])
{
    // unexpected(); // 不预期的函数被调用
   functionAbouException();



    cout << "Hello World!" << endl;
    return 0;
}


















