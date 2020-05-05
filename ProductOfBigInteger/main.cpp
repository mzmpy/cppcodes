#include <iostream>
#include <cstdlib>
#include <cstring>

#define M 100   // 预定义储存大整数的数组长度为 100 
char stra[1000];
char strb[1000];

typedef struct _Node
{
    int arr[M];
    int len;
    int power;
} Node, *pNode;

void seperation(pNode src, pNode des, int begin, int len)   // 将一个 n 位数的第 begin 位到第 begin+len 位
{                                                           // 的部分分离出来
    for(int i=begin, j=0; i<begin+len; ++i, ++j)
    {
        des->arr[j] = src->arr[i];
    }
    des->len = len;
    des->power = src->power + begin;
}

void addtion(pNode pInta, pNode pIntb, pNode ans)   // 将两个数按位相加
{
    int i, buff, znum, pIntaLen, pIntbLen, len;   // buff 用于记录相加时的进位
    int buffa, buffb;   // 记录 pInta ，pInb 相加时对应位上的数字
    pNode pbuff;
    if(pInta->power < pIntb->power)   // 保证 pInta 的幂数更大
    {
        pbuff = pInta;
        pInta = pIntb;
        pIntb = pbuff;
    }
    ans->power = pIntb->power;
    buff = 0;
    pIntaLen = pInta->power + pInta->len;
    pIntbLen = pIntb->power + pIntb->len;
    if(pIntaLen>pIntbLen)
        len = pIntaLen;
    else
        len = pIntbLen;
    znum = pInta->power - pIntb->power;
    for(i=0; i<len-ans->power; ++i)
    {
        if(i<znum)
            buffa = 0;
        else
            buffa = pInta->arr[i-znum];
        
        if(i<pIntb->len)
            buffb = pIntb->arr[i];
        else
            buffb = 0;
        if(i>=pInta->len+znum)
            buffa = 0;
        
        ans->arr[i] = (buffa + buffb + buff) % 10;
        buff = (buffa + buffb + buff) / 10;
    }
    if(buff>0)
        ans->arr[i++] = buff;
    ans->len = i;
}

void multiplication(pNode pInta, pNode pIntb, pNode ans)
{
    int i, buff;
    int spbega = (pInta->len)>>1, spbegb = (pIntb->len)>>1;   // 定义分割的起点
    Node pIntaL, pIntaH, pIntbL, pIntbH;
    Node res1, res2, res3, res4, res;
    pNode pbuff;
    if(!spbega || !spbegb)   // 如果分割起点为0，意味着整数的位数为1
    {
        if(!spbega)   // 如果 pInta 的长度为1，则交换 pInta 和 pIntb ，保证 pInta 的长度大于或等于 pIntb
        {
            pbuff = pInta;
            pInta = pIntb;
            pIntb = pbuff;
        }
        ans->power = pInta->power + pIntb->power;
        buff = 0;
        for(i=0; i<pInta->len; ++i)
        {
            ans->arr[i] = ((pIntb->arr[0])*(pInta->arr[i])+buff) % 10;
            buff = ((pIntb->arr[0])*(pInta->arr[i])+buff) / 10;
        }
        if(buff>0)
            ans->arr[i++] = buff;
        ans->len = i;
        return;
    }

    seperation(pInta, &pIntaH, spbega, (pInta->len)-spbega);
    seperation(pInta, &pIntaL, 0, spbega);
    seperation(pIntb, &pIntbH, spbegb, (pIntb->len)-spbegb);
    seperation(pIntb, &pIntbL, 0, spbegb);

    multiplication(&pIntaH, &pIntbH, &res1);   // 递归调用
    multiplication(&pIntaH, &pIntbL, &res2);
    multiplication(&pIntaL, &pIntbH, &res3);
    multiplication(&pIntaL, &pIntbL, &res4);

    addtion(&res3, &res4, ans);
    addtion(&res2, ans, &res);
    addtion(&res1, &res, ans);
}

int main()
{
    Node ans, Inta, Intb, ans_add, ans_pro;

    std::cout << "输入大整数 a : ";
    std::cin >> stra;
    std::cout << "输入大整数 b : ";
    std::cin >> strb;
    Inta.len = strlen(stra);
    Intb.len = strlen(strb);

    for(int i=Inta.len-1, j=0; i>=0; --i)
    {
        Inta.arr[i] = stra[j++] - '0';
    }
    Inta.power = 0;

    for(int i=Intb.len-1, j=0; i>=0; --i)
    {
        Intb.arr[i] = strb[j++] - '0';
    }
    Intb.power = 0;
/*
    for(int i=Inta.len-1; i>=0; --i)
        std::cout << Inta.arr[i];
    std::cout << std::endl;
    for(int i=Intb.len-1; i>=0; --i)
        std::cout << Intb.arr[i];
    std::cout << std::endl;

    addtion(&Inta, &Intb, &ans_add);
    for(int i=ans_add.len-1; i>=0; --i)
        std::cout << ans_add.arr[i];
    std::cout << std::endl;

    multiplication(&Inta, &Intb, &ans_pro);
    for(int i=ans_pro.len-1; i>=0; --i)
        std::cout << ans_pro.arr[i];
    std::cout << std::endl;
*/
    multiplication(&Inta, &Intb, &ans);
    std::cout << "最终结果：";
    for(int i=ans.len-1; i>=0; --i)
        std::cout << ans.arr[i];
    std::cout << std::endl;
    return 0;
}






