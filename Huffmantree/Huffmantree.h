#pragma once

//哈夫曼树结构体定义 为顺序表的形式
typedef struct
{
	double weight;
	int parent;
	int lchild;
	int rchild;
}HTNode,*HuffmanTree;
//将字符串数组定义为HuffmanCode
typedef char** HuffmanCode;
//统计的字符信息及编码 结构体定义
typedef struct
{
	char character;
	int num;
	double weight;
	char *Code;
	int Bincode;
 }WeightCr,*Wtchar;
//统计各字符频率
void Statistics(char* strFile,Wtchar& ch, int& mx,int& n)
{
	//整体采用哈希表的思想 可用map映射代替
	char c; int vis[200]; int nf = 0;
	memset(vis, 0, sizeof(vis));//初始化统计数组
	//打开文件
	FILE*fp = fopen(strFile, "rt");
	if (!fp)
	{
		printf("Error:can not open the file!");
		exit(OVERFLOW);
	}
	//读取文件
	while (!feof(fp))
	{
		fscanf(fp, "%c", &c);
		vis[c]++;//每个字符都有对应的ASCII码 具有一一对应的关系
		nf++;
	}
	mx = nf-1;
	//统计总体字符个数
	int i=0, j=0;
	for (i = 0; i < 200; i++)
	{
		if (vis[i] != 0)j++;
	}
    //分配内存
	ch = new WeightCr[j];
	n = j;
	j = 0;
	//遍历统计数组 存入每个字符的数据
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
//找出哈夫曼树中权重值最小的两个结点
void Select(HuffmanTree HT, int n, int &s1, int &s2)
{
	double w1 = 1.0; double w2 = 1.0;
	//先使用遍历找出1个
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent == 0) {
			if (HT[i].weight <= w1) {
				w1 = HT[i].weight;
				s1 = i;
			}
		}
	}
	//再遍历一次同时限定条件 i!=s1
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
//创建哈夫曼树
void CreatHuffmantree(HuffmanTree& HT, WeightCr*ch, int n)
{
	if (n <= 1) {
		printf("ERROR:can not create the Huffmantree!");
		return;
	}
	int i = 0;
	int m = 2 * n - 1;//除去叶结点 还需要n-1个结点（每次找两个构成新结点）
	HT = new HTNode[m + 1];//申请空间 将第一个结点空出 因此需要申请m+1个结点空间
	//初始化原始字符结点
	for (i = 1; i <= n; i++)
	{
		HT[i].weight = ch[i - 1].weight;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	//初始化结合而成的新结点
	for (i = n + 1; i <= m;i++)
	{
		HT[i].weight = 0;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	//计算并赋值 不断创建
	for (i = n + 1; i <= m; i++)
	{
		int s1, s2;
		Select(HT, i - 1, s1, s2);
		//第i个结点是由s1 s2两个结点所构成的
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}
//编码哈夫曼树
void HuffmanCoding(HuffmanTree HT, WeightCr* ch,int n)
{
	int i; int start; int c; int f;
	char* str = new char[n];//本身编码长度最多应为n-1（编码的最长长度）最后一位要为终止符，所以多开一位
	str[n - 1] = '\0';//最后一位赋'\0' 并将start从n-1开始
	//找每一个1——n的结点（字符）对应的编码
	for (i = 1; i <= n; i++)
	{
		start = n - 1;
		//遍历哈夫曼树从叶结点逆向找到根结点 逆向进行编码
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
		{
			if (HT[f].lchild == c)str[--start] = '0';
			else str[--start] = '1';
		}
		//将编码录入字符数据中
		ch[i-1].Code = new char[n - start];
		strcpy(ch[i - 1].Code, &str[start]);
	}
}
//将原文档编码输出
void Encoding(char* strFile1, char* strFile2, Wtchar ch,int n)
{
	//打开文件
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
	//遍历文档 一个个字符依次比较判断 输入
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
		if (feof(fp1))break;//防止最后一个字符多编码一次
		fprintf(fp2, "%s", str);
	}
	//关闭文件
	fclose(fp1);
	fclose(fp2);
}
//再将编码文档重新解码
void Decoding(char* strFile2, char* strFile3, Wtchar ch, int n)
{
	//定义 初始化中间变量
	char c; char str[60]; bool find = false;
	memset(str, 0, sizeof(str));
	//打开文件
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
	//使用双循环先存到字符串 再将字符串与Code编码进行匹配
	while (!feof(fp1))
	{
		for (int i = 0; i < n-1; i++)
		{
			fscanf(fp1, "%c", &str[i]);
			for (int j = 0; j < n; j++)
			{
				if (strcmp(str, ch[j].Code) == 0) {
					memset(str, 0, sizeof(str));//将str字符串重新设置为0
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
	//关闭文件
	fclose(fp1);
	fclose(fp2);
}
//对哈夫曼树二进制编码
void BinHuffmanCoding(HuffmanTree HT, Wtchar& ch, int n)
{
	int i; int t=0; int c; int f;//编码用一个int型的储存（32位足够） 初始化为00000000（32个0）
	for (i = 1; i <= n; i++)
	{
		//遍历哈夫曼树从叶结点逆向找到根结点 逆向进行编码 
		//但与上面的编码方法相比 编码颠倒存储 前置位归0
		//因为前者编码方法编码具有唯一性 故该编码也具有唯一性 但是可能不太常用（属于自己乱造的）
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
		{
			if (HT[f].lchild == c)t=t << 1;//将编码往前移位并使最右一位为0
			else t=t<<1|1;//将编码往前移位并使最右一位为1
		}
		//将编码录入字符数据中
		ch[i - 1].Bincode = t;
		t = 0;
	}
}
//将原文档用二进制编码输出
void BinEncoding(char* strFile1, char* strFile4, Wtchar ch, int n)
{
	//打开文件
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
	//遍历文档 一个个字符依次比较判断 输入
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
		if (feof(fp1))break;//防止最后一个字符多编码一次
		mx++;
	}
	fwrite(t, sizeof(int), mx, fp2);
	//关闭文件
	fclose(fp1);
	fclose(fp2);
 }
//将二进制编码文档解码输出
void BinDecoding(char* strFile4, char* strFile5, Wtchar ch, int n,int mx)
{
	//定义 初始化中间变量
	char c;  int t[2500];
	//打开文件
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
	//将二进制文件读入到t[length_NF]数组中
	fread(t, sizeof(int), mx, fp1);
	//遍历数组 找到对应的字符 并输出
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
	//关闭文件
	fclose(fp1);
	fclose(fp2);
}
