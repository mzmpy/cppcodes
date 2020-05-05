# include <iostream>

const int N = 100;
int n;
int strategy[N][N];
double m[N][N], strings[N][N];

void TriangulatioOfConvexpolygon()
{
    for(int i=1; i<=n; ++i)
    {
        strategy[i][i] = 0;
        m[i][i] = 0;
    }

    for(int d=2; d<=n; ++d)
        for(int i=1; i<=n-d+1; ++i)
        {
            int j = i + d - 1;
            m[i][j] = m[i+1][j] + strings[i-1][i] +strings[i][j] + strings[j][i-1];
            strategy[i][j] = i;
            for(int k=i+1; k<j; ++k)
            {
                double tmp = m[i][k] + m[k+1][j] + strings[i-1][k] + strings[k][j] + strings[j][i-1];
                if(m[i][j] > tmp)
                {
                    m[i][j] = tmp;
                    strategy[i][j] = k;
                }
            }
        }
}

void print(int sp, int ep)
{
    if(sp == ep) return;
    if(strategy[sp][ep]>sp)
        std::cout << "{v" << sp-1 << "v" << strategy[sp][ep] << "}" <<std::endl;
    if(ep>strategy[sp][ep]+1)
        std::cout << "{v" << strategy[sp][ep] << "v" << ep << "}" <<std::endl;
    print(sp, strategy[sp][ep]);
    print(strategy[sp][ep]+1, ep);
}

int main()
{
    int i, j;
    std::cout << "请输入顶点的个数：";
    std::cin >> n;
    --n;
    std::cout << "请依次输入各顶点的连接权值：" << std::endl;
    for(int i=0; i<=n; ++i)
        for(int j=0; j<=n; ++j)
        {
            std::cin >> strings[i][j];
        }
    TriangulatioOfConvexpolygon();
    std::cout << m[1][n] << std::endl;
    print(1, n);
    return 0;
}


