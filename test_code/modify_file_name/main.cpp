#include <iostream>
#include <string>
#include <io.h>
#include <stdlib.h>
#include <vector>


using namespace std;

string dirpath = "C:\\Users\\AndroidDev\\Desktop\\test\\325X325\\";

int main()
{
    _finddata_t file;
    long lf;
    char suffixs[] = "*.png";      //要寻找的文件类型
    vector<string> fileNameList;   //文件夹下.png类型文件的名字向量
    char *p;
    p = (char *)malloc((dirpath.size()+1)*sizeof(char));
    strcpy(p, dirpath.c_str());

    //获取文件名向量
    if ((lf = _findfirst(strcat(p, suffixs), &file)) == -1l)
    {
        cout<<"Not Fund File!\n";
    }
    else
    {
        cout<<"\nFile list:\n";
        do {
            cout<<file.name<<endl;
            //str是用来保存文件名的字符串string
            string str(file.name);
            fileNameList.push_back(str);
            cout<<endl;
        }while(_findnext(lf, &file) == 0);
    }
    _findclose(lf);

    //遍历文件名向量，并进行修改

    static int i = 1;
    char buf[] = "product_1_big.png";

    for (vector<string>::iterator iter = fileNameList.begin(); iter != fileNameList.end(); ++iter)
    {
        sprintf(buf,"product_%d_big.png",i++);
        string strAdd = buf;   //在原文件名的基础上要增加的部分 命名要这里下功夫

        string oldName = dirpath+*iter;
        //str1为原文件名要保留的部分
        string str1;
        str1 = (*iter).substr(0,0); // 指定在某一个位置添加修改文件名
        string newName = dirpath+str1+strAdd; // 在原来的基础上添加文件名部分
        cout<<"oldName:"<<oldName<<endl;
        cout<<"newName"<<newName<<endl;

        cout<<"oldName size = "<<oldName.size()<<endl;
        cout<<"newName size = "<<newName.size()<<endl;

        char *oldNamePointer, *newNamePointer;
        oldNamePointer = (char *)malloc((oldName.size()+1) * sizeof(char));
        newNamePointer = (char *)malloc((newName.size()+1) * sizeof(char));
        strcpy(oldNamePointer, oldName.c_str());
        strcpy(newNamePointer, newName.c_str());
        cout<<oldNamePointer<<endl;
        cout<<newNamePointer<<endl;

        rename(oldNamePointer, newNamePointer);

        free(oldNamePointer);
        free(newNamePointer);
    }
    system("PAUSE");
    return 0;
}


