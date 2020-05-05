#include <iostream>
 
#define N 100

int rent[N][N],  min[N][N], strategy[N][N];
int num;

void BestRenting()
{
    for(int d=3; d<=num; ++d)
    {
        for(int i=0; i<=num-d+1; ++i)
        {
            int j = i+d-1;
            for(int k=i+1; k<j; ++k)
            {
                int tmp = min[i][k] + min[k][j];
                if(min[i][j] > tmp)
                {
                    min[i][j] = tmp;
                    strategy[i][j] = k;
                }
            }
        }
    }
}

void print(int begin, int end)
{
    int k = strategy[begin][end];
    if(!k)
    {
        std::cout << "-" << end;
        return;
    }
    print(begin, k);
    print(k, end);
}

int main()
{
    std::cout<< "输入站点个数：";
    std::cin >> num;
    std::cout<< "依次输入各站点之间的租金：";
    for(int i=0; i<num; ++i)
        for(int j=i+1; j<num; ++j)
        {
            std::cin >> rent[i][j];
            min[i][j] = rent[i][j];
        }
    BestRenting();
    std::cout << "花费的最少租金为：" << min[0][num-1] << std::endl;
    std::cout << "最少租金经过的站点：" << 0;
    print(0, num-1);
    std::cout << std::endl;
    return 0; 
}




