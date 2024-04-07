#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
using namespace std;
#define OK 1
#define ERROR 0

//链表的结构体定义
typedef struct LNode {
	int num;
	int place;
	LNode* next;
}LNode, * LinkList;

void Getdata(LinkList& head, LinkList& L, char* a)
{
	//顺式创建链表
	int i;
	LinkList prev, pt;
	prev = new LNode;
	head = prev;
	for (i = 0; i < strlen(a); i++)
	{
		L = new LNode;
		L->num = (int)a[strlen(a) - i - 1] - 48;
		L->place = i + 1;
		L->next = NULL;
		prev->next = L;
		prev = L;
	}
	return;
}
//判断两个位数相加是否需要进位
bool Add(int a, int b, int& c)
{
	c += a + b;
	if (c >= 10)
	{
		c = c - 10;
		return true;
	}
	if (c < 10)return false;
}

int main()
{
	char BigNumber1[256];
	char BigNumber2[256];
	//打开文件
	char strFile[256] = "D:\\DataStructure\\BigNumber\\Data\\BigNumber.txt";
	FILE* fp = fopen(strFile, "r+");
	if (!fp)
	{
		printf("Error:can not open the file :%s", strFile);
		return 1;
	}
	//读入大数1和大数2
	fscanf(fp, "%s", BigNumber1);
	fscanf(fp, "%s", BigNumber2);
	int result[256] = { 0 };//初始化结果数组
	//声明一些变量
	LinkList head1, head2, p1, p2, head, prev, pt, q;
	int nLen1 = strlen(BigNumber1);
	int nLen2 = strlen(BigNumber2);
	int i, Lmax; int t;
	if (nLen1 > nLen2)	Lmax = nLen1;
	else	Lmax = nLen2;
	//创建Bignumber1和2的链表
	Getdata(head1, p1, BigNumber1);
	Getdata(head2, p2, BigNumber2);
	//初始化结果链表的头指针和第一位
	head = new LNode;
	pt = new LNode;
	pt->place = 1;
	pt->num = 0;
	head->next = pt;
	p1 = head1->next;
	p2 = head2->next;
	//创建链表并计算
	for (i = 1; i <= Lmax; i++)
	{
		q = new LNode;
		q->place = i + 1;
		//声明变量a b用于储存数据 防止指针变量改变
		int a; int b;
		if (p1 == NULL)a = 0;
		else a = p1->num;
		if (p2 == NULL)b = 0;
		else b = p2->num;
		//使用bool函数 若返回值为true则初始化下一位为1 false则初始化下一位为0
		if (Add(a, b, pt->num))
		{
			q->num = 1;
			t = 1;
		}
		else
		{
			q->num = 0;
			t = 0;
		}
		//所有链表指针均后移
		q->next = NULL;
		pt->next = q;
		pt = q;
		if (p1 != NULL)p1 = p1->next;
		if (p2 != NULL)p2 = p2->next;
	}
	//遍历结果链表并存入数组
	pt = head->next;
	for (i = 0; i < Lmax + t; i++)
	{
		result[i] = pt->num;
		pt = pt->next;
	}
	//打印
	fprintf(fp, " ");
	for (i = Lmax - 1 + t; i >= 0; i--) {
		fprintf(fp, "%d", result[i]);
	}
	fprintf(fp, " ");
	for (i = Lmax - 1 + t; i >= 0; i--) {
		fprintf(fp, "(%d,%d)", i + 1, result[i]);
	}
	//关闭文件
	fclose(fp);
}
