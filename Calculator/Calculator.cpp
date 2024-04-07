// Calculator.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include"Calculator.h"

int main()
{
    char c, x, prev,op;
    int a, b, num; 
    //打开文件
    char strFile[256] = "D:\\DataStructure\\Calculator\\Data\\formula.txt";
    FILE* fp = fopen(strFile, "r+");
    if (!fp)
    {
        printf("Error:can not open the file!");
        return 0;
    }
    //创建两个栈
    NumStack OPND;
    CharStack OPTR;
    CreatnStack(OPND);
    CreatStack(OPTR);

    Push(OPTR, '#'); //字符栈底放入'#'
    prev = '#';
    fscanf(fp, "%c", &c);

    while (c != '#'||GetTop(OPTR)!='#')
    {
        //若c为数字
        if (Cmpnum(c)) {
            //若上一个入栈元素也为数字 则对上一个入栈元素进行操作使其增加一位
            if (Cmpnum(prev)) {
                nPop(OPND, num);
                nPush(OPND, num * 10 + int(c - '0'));
            }
            //若上一个入栈元素不为数字 则直接将c入栈
            else {
                 nPush(OPND, int(c - '0'));
            } 
            prev = c;
            fscanf(fp, "%c", &c);
        }
        //若c为运算符
        else
        {
            //进行上一个入栈运算符与当前运算符的优先级比较
            switch (Cmppri(GetTop(OPTR),c))
            {
            //若为< 则将当前运算符入栈并继续读取算式
            case'<':
                Push(OPTR, c);
                prev = c;
                fscanf(fp, "%c", &c);
                break;
            //若为= 则定为（）消除 或者算式结束  弹出栈顶元素即可实现消除
            case'=':
                Pop(OPTR, x);
                prev = c;
                fscanf(fp, "%c", &c);
                break;
            //若为> 则弹出字符栈顶元素 和两个数栈顶元素 进行运算 并将结果压入数栈中 同时不对c进行更改进行下一次循环
            case'>':
                Pop(OPTR, op);
                nPop(OPND, b);
                nPop(OPND, a);
                nPush(OPND, Opreate(a, op, b));
                break;
            case'w':
                return 0;
            default:
                break;
            }
        }
    }
    fprintf(fp,"\n%d\n",GetnTop(OPND));

    std::cout << "Hello World!\n";
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
