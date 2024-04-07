#pragma once

//���������ṹ�嶨�� Ϊ˳������ʽ
typedef struct
{
	double weight;
	int parent;
	int lchild;
	int rchild;
}HTNode,*HuffmanTree;
//���ַ������鶨��ΪHuffmanCode
typedef char** HuffmanCode;
//ͳ�Ƶ��ַ���Ϣ������ �ṹ�嶨��
typedef struct
{
	char character;
	int num;
	double weight;
	char *Code;
	int Bincode;
 }WeightCr,*Wtchar;
//ͳ�Ƹ��ַ�Ƶ��
void Statistics(char* strFile,Wtchar& ch, int& mx,int& n)
{
	//������ù�ϣ���˼�� ����mapӳ�����
	char c; int vis[200]; int nf = 0;
	memset(vis, 0, sizeof(vis));//��ʼ��ͳ������
	//���ļ�
	FILE*fp = fopen(strFile, "rt");
	if (!fp)
	{
		printf("Error:can not open the file!");
		exit(OVERFLOW);
	}
	//��ȡ�ļ�
	while (!feof(fp))
	{
		fscanf(fp, "%c", &c);
		vis[c]++;//ÿ���ַ����ж�Ӧ��ASCII�� ����һһ��Ӧ�Ĺ�ϵ
		nf++;
	}
	mx = nf-1;
	//ͳ�������ַ�����
	int i=0, j=0;
	for (i = 0; i < 200; i++)
	{
		if (vis[i] != 0)j++;
	}
    //�����ڴ�
	ch = new WeightCr[j];
	n = j;
	j = 0;
	//����ͳ������ ����ÿ���ַ�������
	for (i = 0; i < 200; i++)
	{
		if (vis[i] != 0) {
			ch[j].character = i;
			ch[j].num = vis[i];
			ch[j].weight = ch[j].num*1.0 / nf;
			j++;
		}
	}
}
//�ҳ�����������Ȩ��ֵ��С���������
void Select(HuffmanTree HT, int n, int &s1, int &s2)
{
	double w1 = 1.0; double w2 = 1.0;
	//��ʹ�ñ����ҳ�1��
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent == 0) {
			if (HT[i].weight <= w1) {
				w1 = HT[i].weight;
				s1 = i;
			}
		}
	}
	//�ٱ���һ��ͬʱ�޶����� i!=s1
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent == 0) {
			if (HT[i].weight <= w2 && i != s1) {
				w2 = HT[i].weight;
				s2 = i;
			}
		}
	}
}
//������������
void CreatHuffmantree(HuffmanTree& HT, WeightCr*ch, int n)
{
	if (n <= 1) {
		printf("ERROR:can not create the Huffmantree!");
		return;
	}
	int i = 0;
	int m = 2 * n - 1;//��ȥҶ��� ����Ҫn-1����㣨ÿ�������������½�㣩
	HT = new HTNode[m + 1];//����ռ� ����һ�����ճ� �����Ҫ����m+1�����ռ�
	//��ʼ��ԭʼ�ַ����
	for (i = 1; i <= n; i++)
	{
		HT[i].weight = ch[i - 1].weight;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	//��ʼ����϶��ɵ��½��
	for (i = n + 1; i <= m;i++)
	{
		HT[i].weight = 0;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	//���㲢��ֵ ���ϴ���
	for (i = n + 1; i <= m; i++)
	{
		int s1, s2;
		Select(HT, i - 1, s1, s2);
		//��i���������s1 s2������������ɵ�
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}
//�����������
void HuffmanCoding(HuffmanTree HT, WeightCr* ch,int n)
{
	int i; int start; int c; int f;
	char* str = new char[n];//������볤�����ӦΪn-1�����������ȣ����һλҪΪ��ֹ�������Զ࿪һλ
	str[n - 1] = '\0';//���һλ��'\0' ����start��n-1��ʼ
	//��ÿһ��1����n�Ľ�㣨�ַ�����Ӧ�ı���
	for (i = 1; i <= n; i++)
	{
		start = n - 1;
		//��������������Ҷ��������ҵ������ ������б���
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
		{
			if (HT[f].lchild == c)str[--start] = '0';
			else str[--start] = '1';
		}
		//������¼���ַ�������
		ch[i-1].Code = new char[n - start];
		strcpy(ch[i - 1].Code, &str[start]);
	}
}
//��ԭ�ĵ��������
void Encoding(char* strFile1, char* strFile2, Wtchar ch,int n)
{
	//���ļ�
	char c; char*str=new char[n-1];
	FILE* fp1 = fopen(strFile1, "rt");
	if (!fp1)
	{
		printf("Error:can not open the file!");
		exit(OVERFLOW);
	}
	FILE* fp2 = fopen(strFile2, "wt");
	if (!fp2)
	{
		printf("Error:can not open the file!");
		exit(OVERFLOW);
	}
	//�����ĵ� һ�����ַ����αȽ��ж� ����
	while (!feof(fp1))
	{
		fscanf(fp1, "%c", &c);
		for (int i = 0; i < n; i++)
		{
			if (c == ch[i].character) {
				strcpy(str, ch[i].Code);
				break;
			}
		}
		if (feof(fp1))break;//��ֹ���һ���ַ������һ��
		fprintf(fp2, "%s", str);
	}
	//�ر��ļ�
	fclose(fp1);
	fclose(fp2);
}
//�ٽ������ĵ����½���
void Decoding(char* strFile2, char* strFile3, Wtchar ch, int n)
{
	//���� ��ʼ���м����
	char c; char str[60]; bool find = false;
	memset(str, 0, sizeof(str));
	//���ļ�
	FILE* fp1 = fopen(strFile2, "rt");
	if (!fp1)
	{
		printf("Error:can not open the file!");
		exit(OVERFLOW);
	}
	FILE* fp2 = fopen(strFile3, "wt");
	if (!fp2)
	{
		printf("Error:can not open the file!");
		exit(OVERFLOW);
	}
	//ʹ��˫ѭ���ȴ浽�ַ��� �ٽ��ַ�����Code�������ƥ��
	while (!feof(fp1))
	{
		for (int i = 0; i < n-1; i++)
		{
			fscanf(fp1, "%c", &str[i]);
			for (int j = 0; j < n; j++)
			{
				if (strcmp(str, ch[j].Code) == 0) {
					memset(str, 0, sizeof(str));//��str�ַ�����������Ϊ0
					c = ch[j].character;
					find = true;
					fprintf(fp2, "%c", c);
					break;
				}
			}
			if (find) {
				find = false;
				break;
			}
		}
	}
	//�ر��ļ�
	fclose(fp1);
	fclose(fp2);
}
//�Թ������������Ʊ���
void BinHuffmanCoding(HuffmanTree HT, Wtchar& ch, int n)
{
	int i; int t=0; int c; int f;//������һ��int�͵Ĵ��棨32λ�㹻�� ��ʼ��Ϊ00000000��32��0��
	for (i = 1; i <= n; i++)
	{
		//��������������Ҷ��������ҵ������ ������б��� 
		//��������ı��뷽����� ����ߵ��洢 ǰ��λ��0
		//��Ϊǰ�߱��뷽���������Ψһ�� �ʸñ���Ҳ����Ψһ�� ���ǿ��ܲ�̫���ã������Լ�����ģ�
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
		{
			if (HT[f].lchild == c)t=t << 1;//��������ǰ��λ��ʹ����һλΪ0
			else t=t<<1|1;//��������ǰ��λ��ʹ����һλΪ1
		}
		//������¼���ַ�������
		ch[i - 1].Bincode = t;
		t = 0;
	}
}
//��ԭ�ĵ��ö����Ʊ������
void BinEncoding(char* strFile1, char* strFile4, Wtchar ch, int n)
{
	//���ļ�
	char c; int t[2500]; int mx = 0;
	FILE* fp1 = fopen(strFile1, "rt");
	if (!fp1)
	{
		printf("Error:can not open the file!");
		exit(OVERFLOW);
	}
	FILE* fp2 = fopen(strFile4, "wb");
	if (!fp2)
	{
		printf("Error:can not open the file!");
		exit(OVERFLOW);
	}
	//�����ĵ� һ�����ַ����αȽ��ж� ����
	while (!feof(fp1))
	{
		fscanf(fp1, "%c", &c);
		for (int i = 0; i < n; i++)
		{
			if (c == ch[i].character) {
				t[mx] = ch[i].Bincode;
				break;
			}
		}
		if (feof(fp1))break;//��ֹ���һ���ַ������һ��
		mx++;
	}
	fwrite(t, sizeof(int), mx, fp2);
	//�ر��ļ�
	fclose(fp1);
	fclose(fp2);
 }
//�������Ʊ����ĵ��������
void BinDecoding(char* strFile4, char* strFile5, Wtchar ch, int n,int mx)
{
	//���� ��ʼ���м����
	char c;  int t[2500];
	//���ļ�
	FILE* fp1 = fopen(strFile4, "rb");
	if (!fp1)
	{
		printf("Error:can not open the file!");
		exit(OVERFLOW);
	}
	FILE* fp2 = fopen(strFile5, "wt");
	if (!fp2)
	{
		printf("Error:can not open the file!");
		exit(OVERFLOW);
	}
	//���������ļ����뵽t[length_NF]������
	fread(t, sizeof(int), mx, fp1);
	//�������� �ҵ���Ӧ���ַ� �����
	for (int i = 0; i < mx; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (t[i] == ch[j].Bincode) {
				c = ch[j].character;
				break;
			}
		}
		fprintf(fp2, "%c", c);
	}		
	//�ر��ļ�
	fclose(fp1);
	fclose(fp2);
}
