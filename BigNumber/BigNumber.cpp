#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
using namespace std;
#define OK 1
#define ERROR 0

//����Ľṹ�嶨��
typedef struct LNode {
	int num;
	int place;
	LNode* next;
}LNode, * LinkList;

void Getdata(LinkList& head, LinkList& L, char* a)
{
	//˳ʽ��������
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
//�ж�����λ������Ƿ���Ҫ��λ
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
	//���ļ�
	char strFile[256] = "D:\\DataStructure\\BigNumber\\Data\\BigNumber.txt";
	FILE* fp = fopen(strFile, "r+");
	if (!fp)
	{
		printf("Error:can not open the file :%s", strFile);
		return 1;
	}
	//�������1�ʹ���2
	fscanf(fp, "%s", BigNumber1);
	fscanf(fp, "%s", BigNumber2);
	int result[256] = { 0 };//��ʼ���������
	//����һЩ����
	LinkList head1, head2, p1, p2, head, prev, pt, q;
	int nLen1 = strlen(BigNumber1);
	int nLen2 = strlen(BigNumber2);
	int i, Lmax; int t;
	if (nLen1 > nLen2)	Lmax = nLen1;
	else	Lmax = nLen2;
	//����Bignumber1��2������
	Getdata(head1, p1, BigNumber1);
	Getdata(head2, p2, BigNumber2);
	//��ʼ����������ͷָ��͵�һλ
	head = new LNode;
	pt = new LNode;
	pt->place = 1;
	pt->num = 0;
	head->next = pt;
	p1 = head1->next;
	p2 = head2->next;
	//������������
	for (i = 1; i <= Lmax; i++)
	{
		q = new LNode;
		q->place = i + 1;
		//��������a b���ڴ������� ��ָֹ������ı�
		int a; int b;
		if (p1 == NULL)a = 0;
		else a = p1->num;
		if (p2 == NULL)b = 0;
		else b = p2->num;
		//ʹ��bool���� ������ֵΪtrue���ʼ����һλΪ1 false���ʼ����һλΪ0
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
		//��������ָ�������
		q->next = NULL;
		pt->next = q;
		pt = q;
		if (p1 != NULL)p1 = p1->next;
		if (p2 != NULL)p2 = p2->next;
	}
	//�������������������
	pt = head->next;
	for (i = 0; i < Lmax + t; i++)
	{
		result[i] = pt->num;
		pt = pt->next;
	}
	//��ӡ
	fprintf(fp, " ");
	for (i = Lmax - 1 + t; i >= 0; i--) {
		fprintf(fp, "%d", result[i]);
	}
	fprintf(fp, " ");
	for (i = Lmax - 1 + t; i >= 0; i--) {
		fprintf(fp, "(%d,%d)", i + 1, result[i]);
	}
	//�ر��ļ�
	fclose(fp);
}
