// Program_1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include<string.h>
#include"Program_1.h"
#include"Timer.h"
using namespace std;

int main()
{
    Timer t;
    //创建结构体变量存储城市和路径的数据
    cities cts;
    cts = new site[MAX_VERTEX_NUM];
    routes rts;
    rts = new route[MAX_ARC_NUM];
    ALGraph G;
    //从文件中读取城市和路径的数据 存入结构体中
    char strFile1[256] = "D:\\DataStructure\\Program_1\\data\\cities.csv";
    char strFile2[256] = "D:\\DataStructure\\Program_1\\data\\routes.csv";
    char strFile3[256] = "D:\\DataStructure\\Program_1\\data\\Graph.htm";
    ReadFileCities(strFile1, cts,G);
    ReadFileRoutes(strFile2, rts,G);
    //创建有向图
    CreateDG(G, cts, rts);    //printfDG(G);编写代码过程中便于调试的遍历打印图函数
    //深度优先遍历图
    DFSTrasval(G);
    //初始化出发地与目的地的变量
    char stcity[64]; char tocity[64]; int nstart; int nend; int model=0;
    memset(stcity,0,sizeof(stcity));
    memset(tocity, 0, sizeof(tocity));
    //读取搜索方式 同时用getchar吃掉换行符号
    printf("请选择您想要的搜索方式：输入1为最短时间，输入2为最少花费\n");
    scanf("%d", &model); getchar();
    //读取始发城市（因可能出现带空格字符的城市 所以采用这种方式代替%s
    //同时用getchar吃掉换行符号
    printf("请输入您的出发地:");
    scanf("%[^\n]", stcity);getchar();
    //同上 读取终达城市
    printf("请输入您的目的地:");
    scanf("%[^\n]", tocity);getchar();
    //找到城市所对应的结点
    Locate(G, stcity, nstart); 
    Locate(G, tocity, nend);
    //根据对应模式找最短路径
    Dispath dp;
    t.Start();
    if (model == 1) {
        Dijkstra1(G, nstart, dp);
        printfShortpaths1(G, dp, nend);
    }
    if (model == 2) {
        Dijkstra2(G, nstart, dp);
        printfShortpaths2(G, dp, nend);
    }
    t.Stop();
    printf("Time elapsed about Dijkstra is : %lf (ms). \n ", t.ElapsedTime());
    //创建htm文件 使路径可视化
    Generatehtml(G, dp, nstart, nend, strFile3,cts);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
