#include <iostream>

using namespace std;

void display(int* arr[],int len)
{

}

int main(int argc, char *argv[])
{
    int arr[10][10] = {0};

    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            cout<< arr[i][j] << " ";
        }
        cout << endl;
    }

    int n=0,m=0;
    static int num = 1;
    while(!arr[n][m])
    {
        if(arr[n][m] == 0)
        {

            arr[n][m++] = num++;

        }
        else
        {
            n+=m;
            arr[--n][m] = num++;
        }
    }

    cout << "-------------------" << endl;

    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            cout<< arr[i][j] << " " ;
        }
         cout << endl;
    }

    return 0;
}
