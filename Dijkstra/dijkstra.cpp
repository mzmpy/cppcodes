// 单源最短路径求解
#include <queue>
#include <iostream>
#include <cstring>
#include <stack>

const int N = 100;
const int INF = 1e7;
int map[N][N], n, m;
int dists[N], flags[N], preNodes[N];   // 分别用来记录每个点从源点到达的最短距离，是否已找到最短路径，连接该点的点

struct Node{
    int node;
    int step;
    int preNode;

    Node() {}   // 构造函数后面不用跟分号
    Node(int n, int sp, int pn=-1) 
    {
        node = n;
        step = sp;
        preNode = pn;
    }

    bool operator< (const Node &nd) const   // 为优先队列 priority_queue<Node> 自动给 Node 排序定义操作符 < 
    {
        return step > nd.step;
    }
};

/* 
Dijkstra单源最短路径求解算法从源点开始，每找到一个点它的自源点到达自己的最短路径，则将该点加
入到一个特殊的子集（这个子集包含源点），每次寻找剩余的点的自源点到达的最短路径时，路径途经的点
都优先从这个子集考虑
*/
void Dijkstra(int start_point)
{
    std::priority_queue<Node> Q;   // 定义优先队列
    Q.push(Node(start_point, 0, start_point));
    memset(flags, 0, sizeof(flags));   // 初始化所有的点都未找到最短路径
    for(int i=0; i<n; i++)
        dists[i] = INF;   // 初始化所有的点自源点到达的距离无穷大
    dists[start_point] = 0;   // 源点到达自己的距离为零

    while(!Q.empty())
    {
        Node cur = Q.top();
        Q.pop();
        int tmp = cur.node;
        // std::cout << tmp << std::endl;
        if(flags[tmp])
            continue;
        flags[tmp] = 1;
        preNodes[tmp] = cur.preNode;
        for(int i=0; i<n; i++)
        {
            if(!flags[i] && map[tmp][i]<INF)
            {
                // std::cout << tmp << " - " << i << " - " << dists[i] << " - " << map[tmp][i] << std::endl;
                if(dists[i]>dists[tmp]+map[tmp][i])
                {
                    dists[i] = dists[tmp] + map[tmp][i];
                    Q.push(Node(i, dists[i], tmp));
                    // std::cout << tmp << " - " << i << " - " << dists[i] << std::endl;
                }
            }
        }
    }
}

void findpath(int start_point, int end_point)
{
    std::cout << "从起点到达终点 " << end_point << " 的路径：";
    std::cout  << end_point;
    int tmp = preNodes[end_point];
    while(tmp != start_point)
    {
        std::cout  << " <-- " << tmp;
        tmp = preNodes[tmp];
    }
    std::cout << " <-- " << tmp << std::endl;
}

int main()
{
    int u, v, w, st;
    /*
    std::cout << "输入城市个数：" << std::endl;
    std::cin >> n;
    std::cout << "输入城市之间的路线个数：" << std::endl;
    std::cin >> m;
    */
    n = 5, m = 7;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            map[i][j] = INF;
    /*
    std::cout << "输入城市u, v的路线以及距离w：" << std::endl;
    while(m--)
    {
        std::cin >> u >> v >> w;
        map[u][v] = std::min(map[u][v], w);
    }
    std::cout << "输入起点：" << std::endl;
    std::cin >> st;
    */
    map[0][1] = 2, map[0][2] = 3, map[1][2] = 5, map[1][3] = 6, map[2][3] = 7, map[2][4] = 1, map[3][4] = 4;
    Dijkstra(0);
    for(int i=0; i<n; i++)
    {
        std::cout << "从位置 " << st << " 到达位置 " << i << "：";
        if(dists[i]==INF)
            std::cout << "无路可达！" << std::endl;
        else
            std::cout << "最短距离：" << dists[i] << std::endl;
    }
    findpath(0, 0);
    findpath(0, 1);
    findpath(0, 2);
    findpath(0, 3);
    findpath(0, 4);
    return 0;
}
