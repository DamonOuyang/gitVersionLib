#include <iostream>

using namespace std;
int* twoSum(int* nums, int numsSize, int target)
{
    int i,a[100]={0},j;
    for(i=0;i<numsSize;i++)
    {
        for(j=0;j<numsSize;j++)
        {
            if(i!=j)
            {
                if(nums[i]+nums[j]==target)
                {
                    a[0]=nums[i];
                    a[1]=nums[j];
                    return (int *)a;
                }

            }
        }
    }
   // return (int *)0;
}
int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    return 0;
}
