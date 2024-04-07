// Huffmantree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include<stdio.h>
#include<string.h>
#include"Huffmantree.h"
using namespace std;

//int main()
//{
//    WeightCr X[8];
//    for (int i = 0; i <8; i++)
//    {
//        X[i].character = 'P' + i;
//        cin >> X[i].weight;
//    }
//    HuffmanTree HT;
//    CreatHuffmantree(HT, X, 8);
//    HuffmanCoding(HT, X, 8);
//    char strFile[256] = "D:\\DIP\\Chapter6\\encodings.txt";
//    FILE* fp = fopen(strFile, "wt");
//    for (int i = 0; i < 8; i++)
//    {
//        fprintf(fp, "P%d  %.2lf  %s\n",i+1,X[i].weight,X[i].Code);
//    }
//    fclose(fp);
//}

int main()
{
	//读入数据并统计频率：ch[n]
    Wtchar ch; int n = 0; int mx = 0;
    char strFile1[256] = "D:\\DataStructure\\Huffmantree\\Data\\school-profile.txt";
	Statistics(strFile1, ch, mx, n);
    //创建哈夫曼树并进行编码
    HuffmanTree HT;
    CreatHuffmantree(HT, ch, n);
    HuffmanCoding(HT, ch, n);
    //将字符对应的编码写入encodings.txt中
    char strFile[256]= "D:\\DataStructure\\Huffmantree\\Data\\encodings.txt";
    FILE* fp = fopen(strFile, "wt");
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%c  %s\n", ch[i].character, ch[i].Code);
    }
    fclose(fp);
    //将文档编码并解码
    char strFile2[256] = "D:\\DataStructure\\Huffmantree\\Data\\school-profile-encodings.txt";
    char strFile3[256] = "D:\\DataStructure\\Huffmantree\\Data\\school-profile-decodings.txt";
    Encoding(strFile1, strFile2, ch, n);
    Decoding(strFile2, strFile3, ch, n);
    //对哈夫曼树进行二进制编码 将文档进行二进制编码并解码
    BinHuffmanCoding(HT, ch, n);
    char strFile4[256] = "D:\\DataStructure\\Huffmantree\\Data\\school-profile-binencodings.data";
    char strFile5[256] = "D:\\DataStructure\\Huffmantree\\Data\\school-profile-bindecodings.txt";
    BinEncoding(strFile1, strFile4, ch, n);
    BinDecoding(strFile4, strFile5, ch, n, mx);

    //编程过程中的一些调试输出数据
    printf("i f l r weight\n");
    for (int i = 1; i <= 2*n-1; i++) {
        printf("%d %d %d %d %lf\n", i, HT[i].parent, HT[i].lchild, HT[i].rchild, HT[i].weight);
    }
    for (int i = 0; i < n; i++) {
        printf("%c %lf %d %s\n", ch[i].character, ch[i].weight,ch[i].Bincode,ch[i].Code);
    }

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
