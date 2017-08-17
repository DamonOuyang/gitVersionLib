#include <iostream>
#include <windows.h>
#include <stdio.h>
using namespace std;

#define MAX_PATH 999999 //

int find_all_files(const char * lpPath)
{
    char szFind[MAX_PATH];
    WIN32_FIND_DATA FindFileData;
    strcpy(szFind,lpPath);
    strcat(szFind,"\\*.*");

    cout<<szFind<<endl;

    HANDLE hFind=::FindFirstFile(szFind,&FindFileData);
    if(INVALID_HANDLE_VALUE == hFind)
        return -1;

    do
    {
        if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if(strcmp(FindFileData.cFileName,".")!=0 && strcmp(FindFileData.cFileName, "..")!=0)
            {
                //发现子目录，递归之
                char szFile[MAX_PATH] = {0};
                strcpy(szFile,lpPath);
                strcat(szFile,"\\");
                strcat(szFile,FindFileData.cFileName);
                find_all_files(szFile);
            }
        }
        else
        {
            //找到文件，处理之
            cout << lpPath << "\\" << FindFileData.cFileName << endl;

            string temporaryName = FindFileData.cFileName;

            string oldName(lpPath);
            oldName += "\\";
            oldName += temporaryName;
            string newName = oldName + ".png";
            //cout<<"newName:"<<newName<<endl;
            //FindFileData.cFileName = temporaryName;
            if (rename(oldName.c_str(), newName.c_str()) == 0)

                //printf("Renamed %s to %s.\n", oldName, newName);
                cout<<oldName+"->"+newName+"\n";

            else

                perror("rename");

            //cout<<"new:"<<FindFileData.cFileName<<endl;

        }
    }while(::FindNextFile(hFind,&FindFileData));

    ::FindClose(hFind);

    return 0;
}


int main()
{
    cout << "Hello world!" << endl;
    char *lpPath = "C:\\Users\\AndroidDev\\Desktop\\test\\325X325";
    find_all_files(lpPath);
    return 0;
}
