// 快速排序算法
#include <iostream>
#include <cstdlib>


int Partition(int arr[], int begin, int end)
{
    int low = begin;
    int high = end;
    int pivot = arr[low];
    while(low<high)
    {
        while(low<high && arr[high]>pivot) high--;   // 自右向左寻找比 pivot 小的节点
        while(low<high && arr[low]<=pivot) low++;   // 自左向右寻找比 pivot 大的节点
        if(low<high)
            std::swap(arr[low++], arr[high--]);   // 交换两个节点的值，最终总是使整个数组左端的节点小于 pivot ，
    }                                             // 右端的节点大于 pivot
    if(arr[high]>pivot)
    {
        std::swap(arr[begin], arr[high-1]);
        return high-1;
    }
    else
    {
        std::swap(arr[begin], arr[high]);
        return high;
    }
}

void QuickSort(int arr[], int begin, int end)
{
    int mid;
    if(begin<end)
    {
        mid = Partition(arr, begin, end);
        QuickSort(arr, begin, mid-1);
        QuickSort(arr, mid+1, end);
    }
}

int main()
{
    int N = 30;
    int List[N];

    for(int i=0; i<N; ++i)
        List[i] = rand() % N;
    
    std::cout << "待排序数组：" << std::endl;
    for(int i=0; i<N; ++i)
        std::cout << List[i] << " ";
    std::cout << std::endl;

    QuickSort(List, 0, N-1);

    std::cout << "排序后数组：" << std::endl;
    for(int i=0; i<N; ++i)
        std::cout << List[i] << " ";
    std::cout << std::endl;

    return 0;
}


