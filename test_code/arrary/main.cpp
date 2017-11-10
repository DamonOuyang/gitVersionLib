#include <iostream>
#include <vector>
#include <deque>
using namespace std;
#define ROW_MAX_SIZE 500
#define COL_MAX_SIZE 500

class Solution {
public:
/**
* @param nums: A list of integers.
* @return: The maximum number inside the window at each moving.
*/
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        // write your code here
        deque<int> q;
        vector<int> res;

        int sz = nums.size();
        // 1,5,7,7,3,2,8,0
        // 7,5,1
        // 0 1 2 3 4 5 6 7  i
        for(int i = 0; i < sz; i++)
        {
            while(q.size() && nums[q.back()] <= nums[i])
                q.pop_back();


            while(q.size() && q.front() <= i - k) // 处理刚开始的几个下标
                q.pop_front();

            q.push_back(i);

            if(i >= k - 1) // 队列中达到滑动窗口个数后，每循环一次，队列处理一次取一个
                res.push_back(nums[q.front()]);
        }
        return res;
    }
};

int main(int argc, char *argv[])
{
    vector<int> nums={1,5,7,7,3,2,8,0};
    Solution s;
    vector<int> res = s.maxSlidingWindow(nums,3); // 滑动窗口中取最大的
    for (int i;i<res.size();i++)
    {
        cout<<res[i] << " ";
    }
}

int main1()
{

    long data[ROW_MAX_SIZE][COL_MAX_SIZE] = {0};

    int row_idex=0;
    int col_idex=0;

    for(long idexData=0; idexData<ROW_MAX_SIZE*COL_MAX_SIZE;)
    {
        for(;col_idex<COL_MAX_SIZE && data[row_idex][col_idex] == 0;++col_idex)
        {
            data[row_idex][col_idex] = ++idexData;
        }
        --col_idex;
        ++row_idex;

        for(;row_idex<ROW_MAX_SIZE && data[row_idex][col_idex] == 0;++row_idex)
        {
            data[row_idex][col_idex] = ++idexData;
        }
        --col_idex;
        --row_idex;

        for(;col_idex >= 0 && data[row_idex][col_idex] == 0;--col_idex)
        {
            data[row_idex][col_idex] = ++idexData;
        }
        ++col_idex;
        --row_idex;

        for(;row_idex >= 0 && data[row_idex][col_idex] == 0;--row_idex)
        {
            data[row_idex][col_idex] = ++idexData;
        }
        ++col_idex;
        ++row_idex;

    }


    // 打印输出
    for(int i = 0; i < ROW_MAX_SIZE; ++i)
    {
        for (int j = 0; j < COL_MAX_SIZE; ++j)
        {
            cout<<data[i][j]<<" ";
        }
        cout<<endl;

    }

    return 0;
}

//    int  data[ROW_MAX_SIZE][COL_MAX_SIZE] = {0};

//    int row_idx = 0;
//    int col_idx = 0;

//    for(int data_idx = 0; data_idx < ROW_MAX_SIZE * COL_MAX_SIZE; )
//    {

//        //上 从左到右
//        for (;col_idx < COL_MAX_SIZE && data[row_idx][col_idx] == 0; ++col_idx)
//        {
//            data[row_idx][col_idx] = ++data_idx;
//        }
//        --col_idx;
//        ++row_idx;

//        //右 从上到下
//        for (;row_idx < ROW_MAX_SIZE && data[row_idx][col_idx] == 0; ++row_idx)
//        {
//            data[row_idx][col_idx] = ++data_idx;
//        }
//        --row_idx;
//        --col_idx;

//        //下 从右到左
//        for (;col_idx >= 0 && data[row_idx][col_idx] == 0; --col_idx)
//        {
//            data[row_idx][col_idx] = ++data_idx;
//        }
//        ++col_idx;
//        --row_idx;

//         //左 从下到上
//        for (;row_idx >= 0 && data[row_idx][col_idx] == 0; --row_idx)
//        {
//            data[row_idx][col_idx] = ++data_idx;
//        }
//        ++row_idx;
//        ++col_idx;
//    }
