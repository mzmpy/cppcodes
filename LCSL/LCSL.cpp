#include <iostream>
#include <cstring>

#define N 1002

int SLLen[N][N], Back[N][N];
char str1[N], str2[N];   // 用于储存相应的序列
int len1, len2;

void LCSL()
{
    for(int i=1; i<=len1; ++i)
        for(int j=1; j<=len2; ++j)
        {
            if(str1[i-1]==str2[j-1])
            {
                SLLen[i][j] = SLLen[i-1][j-1] + 1;
                Back[i][j] = 1;
            }
            else
                if(SLLen[i][j-1]>=SLLen[i-1][j])
                {
                    SLLen[i][j] = SLLen[i][j-1];
                    Back[i][j] = 2;
                }
                else if(SLLen[i-1][j]>SLLen[i][j-1])
                {
                    SLLen[i][j] = SLLen[i-1][j];
                    Back[i][j] = 3;
                }
        }
}

void print(int i, int j)
{
    if(i == 0 || j == 0)
        return;
    if(Back[i][j] == 1)
    {
        print(i-1, j-1);          // 因为 print 其实是回溯的一个过程，根据数组 Back 从后面往回
        std::cout << str1[i-1];   // 寻找最长子序列，因此先 print 再 cout 
    }
    else if(Back[i][j] == 2)
        print(i, j-1);
    else
        print(i-1, j);
    
}

int main()
{
    std::cout << "输入字符串 str1 ：" << std::endl;
    std::cin >> str1;
    std::cout << "输入字符串 str2 ：" << std::endl;
    std::cin >> str2;

    len1 = strlen(str1);
    len2 =  strlen(str2);

    for(int i=0; i<=len1; ++i)
        SLLen[i][0] = 0;
    for(int j=0; j<=len2; ++j)
        SLLen[0][j] = 0;

    LCSL();
    std::cout << "str1 和 str2 的最长公共子序列长度是：" << SLLen[len1][len2] << std::endl;
    std::cout << "str1 和 str2 的最长公共子序列是：";
    print(len1, len2);
    std::cout  << std::endl;

    return 0;
}

















