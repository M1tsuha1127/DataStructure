#pragma once
#define MAX_VERTEX_NUM 256
#define MAX_ARC_NUM 2048
#define INFINE DBL_MAX
#define TRUE 1
#define FALSE 0
//城市结构体cts
typedef struct {
	char country[64];
	char city[64];
	double latitude;
	double longitude;
}site,*cities;
//路线结构体rts
typedef struct {
	char depcity[64];
	char descity[64];
	char way[16];
	double time;
	double cost;
	char info[1024];
}route,*routes;
//邻接表的头结点（链式）
typedef struct ArcNode {
	int adjvex;
	struct ArcNode* nextarc;
	route *rt;
}ArcNode;
//邻接表的表结点（通过链式的头结点所形成的）AdjList为表结点数组 即为邻接表
typedef struct VNode {
	site data;
	ArcNode* firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];
//图的结构（邻接表 顶点数 弧数 辅助遍历(访问)数组）
typedef struct {
	AdjList vertices;
	int vexnum, arcnum;
	int ved[MAX_VERTEX_NUM];//int type  0-not yet  1-visited
}ALGraph;
//路径的结构(dis可理解为决定边量--cost or time)
typedef struct {
	double dis[MAX_VERTEX_NUM];
	int path[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
}Dispath;

void ReadFileCities(char* strFile, cities& cts,ALGraph&G)
{
	//Open the file
	FILE* fp = fopen(strFile, "rt");
	if (!fp) {
		printf("Error:can not open the file %s !", strFile);
		exit(OVERFLOW);
	}
	int i = 0; int j = 0;
	while (!feof(fp))
	{
		//Read country
		char c; 
		fscanf(fp, "%c", &c);
		while (c != ',') 
		{
			cts[i].country[j] = c;
			fscanf(fp, "%c", &c);
			j++;
		}
		cts[i].country[j] = '\0';
		j = 0;

		//Read city
		fscanf(fp, "%c", &c);
		while (c != ',')
		{
			cts[i].city[j] = c;
			fscanf(fp, "%c", &c);
			j++;
		}
		cts[i].city[j] = '\0';
		j = 0;

		//Read latitude and longitude
		fscanf(fp, "%lf", &cts[i].latitude);
		fscanf(fp, "%c", &c);
		fscanf(fp, "%lf\n", &cts[i].longitude);
		i++;
	}
	G.vexnum = i;//Record vexnum
}
void ReadFileRoutes(char* strFile, routes& rts,ALGraph&G)
{
	//Open the file
	FILE* fp = fopen(strFile, "rt");
	if (!fp) {
		printf("Error:can not open the file %s !", strFile);
		exit(OVERFLOW);
	}
	int i = 0; int j = 0;
	while (!feof(fp))
	{
		//Read depcity
		char c;
		fscanf(fp, "%c", &c);
		if (c == '\n')break;
		while (c != ',')
		{
			rts[i].depcity[j] = c;
			fscanf(fp, "%c", &c);
			j++;
		}
		rts[i].depcity[j] = '\0';
		j = 0;

		//Read descity
		fscanf(fp, "%c", &c);
		while (c != ',')
		{
			rts[i].descity[j] = c;
			fscanf(fp, "%c", &c);
			j++;
		}
		rts[i].descity[j] = '\0';
		j = 0;

		//Read way time and cost
		fscanf(fp, "%c", &c);
		while (c != ',')
		{
			rts[i].way[j] = c;
			fscanf(fp, "%c", &c);
			j++;
		}
		rts[i].way[j] = '\0';
		j = 0;

		fscanf(fp, "%lf", &rts[i].time);
		fscanf(fp, "%c", &c);

		fscanf(fp, "%lf\n", &rts[i].cost);
		fscanf(fp, "%c", &c);

		//Read info
		fscanf(fp, "%c", &c);
		while (c != '\n')//use '\n' as end condition
		{
			rts[i].info[j] = c;
			fscanf(fp, "%c", &c);
			j++;
		}
		rts[i].info[j] = '\0';
		j = 0;
		i++;
	}
	G.arcnum = i;//Record arcnum
}
void Locate(ALGraph G,char* city, int& vex)
{
	//Normal loop traversal(can be optimized later.)
	for (int i = 0; i < G.vexnum; i++)
	{
		if (strcmp(G.vertices[i].data.city, city) == 0) {
			vex = i;
			break;
		}
	}
}
route* Locatert(ALGraph G,int start, int end)
{
	//Find the desired path by traversing the chain head node of the adjacency table
	//通过邻接表链式头结点的遍历找到所要的那个路径
	ArcNode* p;
	p = G.vertices[start].firstarc;
	while (p != NULL)
	{
		if (p->adjvex == end)return p->rt;
		p = p->nextarc;
	}
	if (p == NULL)return NULL;
}
void CreateDG(ALGraph& G,cities cts,routes rts)
{
	int i, j; int depvex; int desvex;
	//Store vertices
	for (i = 0; i < G.vexnum; i++)
	{
		strcpy(G.vertices[i].data.city, cts[i].city);
		strcpy(G.vertices[i].data.country, cts[i].country);
		G.vertices[i].data.latitude = cts[i].latitude;
		G.vertices[i].data.longitude = cts[i].longitude;
		G.vertices[i].firstarc = NULL;
		G.ved[i] = 0;//Initialize the auxiliary array
	}
	//Store arc
	for (i = 0; i < G.arcnum; i++)
	{
		Locate(G,rts[i].depcity,depvex);
		Locate(G,rts[i].descity,desvex);
		//Reverse Creation of the chain tables
		ArcNode* arc = new ArcNode;
		arc->adjvex = desvex;
		arc->rt =(rts+i);
		arc->nextarc = G.vertices[depvex].firstarc;
		G.vertices[depvex].firstarc = arc;
	}
}
void DFS(ALGraph &G, int v)
{
	printf("%s-->", G.vertices[v].data.city);
	int w;
	G.ved[v] = TRUE;
	//对顶点v的链表依次遍历 同时每次指针后移就进行dfs递归
	ArcNode* p;
	p = G.vertices[v].firstarc;
	while (p)
	{
		w = p->adjvex;
		if (!G.ved[w])
			DFS(G, w);
		p = p->nextarc;
	}
}
void DFSTrasval(ALGraph &G)
{
	//可能为非连通图 所以要对每个顶点进行dfs遍历
	for (int i = 0; i < G.vexnum; i++)
	{
		if (!G.ved[i])
			DFS(G, i);
	}
	printf("END\n");
}
void Dijkstra1(ALGraph G, int start, Dispath& dp)//第一种dijkstra 以time为变量找最短
{
	int i, j;
	for (i = 0; i < G.vexnum; i++)				// 1. 初始化 距离为无穷，辅助最短路径数组为0
	{
		dp.dis[i] = INFINE;
		dp.path[i][0] = 0;
	}

	ArcNode* p;											// 2. 遍历start链，初始化一些dis和path
	p = G.vertices[start].firstarc;
	while (p)
	{
		dp.dis[p->adjvex] = p->rt->time;
		dp.path[p->adjvex][1] = start;
		dp.path[p->adjvex][2] = p->adjvex;
		dp.path[p->adjvex][3] = -1;
		p = p->nextarc;
	}

	dp.path[start][0] = 1;//以后不再会用到path[start]

	for (i = 0; i < G.vexnum - 1; i++)	//循环3 4（由于start到各点一定最多n-1条mindis，故循环n-1次）
	{

		double mindis = INFINE;					// 3. 找最短路径
		int k;
		for (j = 0; j < G.vexnum; j++)
		{
			if (dp.path[j][0] == 0 && dp.dis[j] < mindis) {
				k = j;
				mindis = dp.dis[j];
			}
		}

		if (mindis == INFINE)return;//如果在连通的图中已经找齐了start到各个点的最短路径 则返回

		dp.path[k][0] = 1;//找到了start到k的最短路

		p = G.vertices[k].firstarc;				 // 4. 更新dis和path
		while (p)
		{

			if (dp.path[p->adjvex][0] == 0 && dp.dis[p->adjvex] > dp.dis[k] + p->rt->time)
			{
				dp.dis[p->adjvex] = dp.dis[k] + p->rt->time;//更新长度dis

				int t = 1;//更新路径path 先把path[k]的拷贝给path[p->adjvex] 再给path[p->adjvex]添上其本身和结束标志
				while (dp.path[k][t] != -1)
				{
					dp.path[p->adjvex][t] = dp.path[k][t];
					t++;
				}
				dp.path[p->adjvex][t] = p->adjvex;
				dp.path[p->adjvex][t + 1] = -1;
			}

			p = p->nextarc;

		}
	}
}
void Dijkstra2(ALGraph G, int start, Dispath &dp)//第二种dijkstra 以cost为变量找最短
{
	int i, j;
	for (i = 0; i < G.vexnum; i++)				// 1. 初始化 距离为无穷，辅助最短路径数组为0
	{
		dp.dis[i] = INFINE;
		dp.path[i][0] = 0;
	}

	ArcNode* p;											// 2. 遍历start链，初始化一些dis和path
	p = G.vertices[start].firstarc;
	while (p)
	{
		dp.dis[p->adjvex] = p->rt->cost;
		dp.path[p->adjvex][1] = start;
		dp.path[p->adjvex][2] = p->adjvex;
		dp.path[p->adjvex][3] = -1;
		p = p->nextarc;
	}

	dp.path[start][0] = 1;//以后不再会用到path[start]
	
	for (i = 0; i < G.vexnum - 1; i++)	//循环3 4（由于start到各点一定最多n-1条mindis，故循环n-1次）
	{
												
		double mindis = INFINE;					// 3. 找最短路径
		int k;
		for (j = 0; j < G.vexnum; j++)
		{
			if (dp.path[j][0] == 0 && dp.dis[j] < mindis) {
				k = j;
				mindis = dp.dis[j];
			}
		}

		if (mindis == INFINE)return;//如果在连通的图中已经找齐了start到各个点的最短路径 则返回

		dp.path[k][0] = 1;//找到了start到k的最短路

		p = G.vertices[k].firstarc;				 // 4. 更新dis和path
		while (p)
		{

			if (dp.path[p->adjvex][0] == 0 && dp.dis[p->adjvex] > dp.dis[k] + p->rt->cost)
			{
				dp.dis[p->adjvex] = dp.dis[k] + p->rt->cost;//更新长度dis

				int t = 1;//更新路径path 先把path[k]的拷贝给path[p->adjvex] 再给path[p->adjvex]添上其本身和结束标志
				while (dp.path[k][t] != -1)
				{
					dp.path[p->adjvex][t] = dp.path[k][t];
					t++;
				}
				dp.path[p->adjvex][t] = p->adjvex;
				dp.path[p->adjvex][t + 1] = -1;
			}

			p = p->nextarc;

		}
	}
}
void printfDG(ALGraph G)
{
	//遍历邻接表
	for (int i = 0; i < G.vexnum; i++)
	{
		printf("%d City:%s - Depcity:", i, G.vertices[i].data.city);
		ArcNode* p;
		p = G.vertices[i].firstarc;
		//遍历每个表结点（链表）
		while (p)
		{
			printf("%s ", p->rt->descity);
			p = p->nextarc;
		}
		printf("\n");
	}
}
void printfShortpaths1(ALGraph G, Dispath& dp,int end)
{
	//若到end结点城市没有路径
	if (dp.dis[end] == INFINE) {
		printf("To City: %s  Can not go to the city!\n", G.vertices[end].data.city);
		return;
	}
	//若到end结点城市已找到最短路径
	else {
		printf("To City: %s  Time: %.2lf hours  Path: %s", G.vertices[end].data.city, dp.dis[end], G.vertices[dp.path[end][1]].data.city);
		//输出路径 以->连接各城市
		for (int j = 2; dp.path[end][j] != -1; j++)
		{
			printf("->%s", G.vertices[dp.path[end][j]].data.city);
		}
		printf("\n");
		return;
	}
}
void printfShortpaths2(ALGraph G, Dispath& dp, int end)
{
	//若到end结点城市没有路径
	if (dp.dis[end] == INFINE) {
		printf("To City: %s  Can not go to the city!\n", G.vertices[end].data.city);
		return;
	}
	//若到end结点城市已找到最短路径
	else {
		printf("To City: %s  Cost: %.2lf dollars  Path: %s", G.vertices[end].data.city, dp.dis[end], G.vertices[dp.path[end][1]].data.city);
		//输出路径 以->连接各城市
		for (int j = 2; dp.path[end][j] != -1; j++)
		{
			printf("->%s", G.vertices[dp.path[end][j]].data.city);
		}
		printf("\n");
	}
	
}
char* Supple(char* c)//某些城市或者info等字符串会出现 ' 的字符 需要在其前面加上'\'
{
	int i = 1;
	int n = strlen(c);
	//读文件的时候就已经将字符串的下一位设置成了'/0' 因此可以将此作为字符串遍历的终止条件
	while (c[i] != '\0')
	{
		//找到 ' 字符
		if (c[i] == '\'') {
			//若它的上一位已经是 \ 字符就跳过本次循环 进行下次循环
			if (c[i - 1] == '\\') {
				i++; continue;
			}
			//将字符串增加一位 并从第i位往后移 且将第i位改为 \ 字符
			c[n+1] = '\0';
			for (int j = n; j > i; j--){ c[j] = c[j - 1]; }
			c[i] = '\\';
			n++;
			i++;
		}
		i++;
	}
	return c;
}
void Generatehtml(ALGraph G,Dispath&dp,int start,int end,char *strFile,cities cts)
{
	//open the file
	FILE* fp = fopen(strFile, "wt");
	if (!fp) {
		printf("Error:can not open the file %s !", strFile);
		exit(OVERFLOW);
	}
	//print the header section
	//打印的时候要注意出现的 ' " 等符号与程序的部分语言所引起的冲突
	//因此手动修改fprintf里涉及到此类符号的内容 
	//并在每次填入字符串的时候使用supple函数进行补\的操作
	std::string s;
	s = "<!DOCTYPE html><html><head><style type='text/css'>body, html{width: 100%;height: 100%;margin:0;font-family:'微软雅黑';}#allmap{height:100%;width:100%;}#r-result{width:100%;}</style><script type='text/javascript' src='http://api.map.baidu.com/api?v=2.0&ak=nSxiPohfziUaCuONe4ViUP2N'></script>";
	fprintf(fp, "%s<title>Shortest path from %s to %s</title></head><body><div id='allmap'></div></div></body></html><script type='text/javascript'>var map = new BMap.Map('allmap');var point = new BMap.Point(0, 0); map.centerAndZoom(point, 2); map.enableScrollWheelZoom(true);", s.c_str(),G.vertices[start].data.city, G.vertices[end].data.city);
	//print the loop section
	//循环打印路径点的创建和城市窗口的创建
	for (int i = 1; dp.path[end][i] != -1 && dp.dis[end] != INFINE; i++)
	{
		fprintf(fp, "var marker%d = new BMap.Marker(new BMap.Point(%lf,%lf)); map.addOverlay(marker%d);", i - 1, cts[dp.path[end][i]].longitude, cts[dp.path[end][i]].latitude, i - 1);
		fprintf(fp, "var infoWindow%d = new BMap.InfoWindow(\"<p style = 'font-size:14px;'>country: %s<br/>city : %s</p>\"); marker%d.addEventListener(\"click\", function () { this.openInfoWindow(infoWindow%d); });", i - 1, Supple(cts[dp.path[end][i]].country), Supple(cts[dp.path[end][i]].city), i - 1, i - 1); 
	}
	//若没找到两点路径（非连通）则只创建标记
	if (dp.dis[end] == INFINE) {
		fprintf(fp, "var marker01 = new BMap.Marker(new BMap.Point(%lf,%lf)); map.addOverlay(marker01);", cts[start].longitude, cts[start].latitude);
		fprintf(fp, "var marker01 = new BMap.Marker(new BMap.Point(%lf,%lf)); map.addOverlay(marker01);", cts[end].longitude, cts[end].latitude);
	}
	//循环打印两点之间路径的创建和路径窗口的创建
	for (int i = 2; dp.path[end][i] != -1 && dp.dis[end] != INFINE; i++)
	{                                                                                                                                                            //两地前者城市的信息：城市 国家                                                                        两地后者城市的信息：城市 国家                                                               定位找到路径在图中的指针所指向的                      交通方式                                                                             时间                                                                                 花费                                                                                     路径所携带的信息
		fprintf(fp, "var contentString%02d = '%s, %s --> %s, %s (%s - %.1lf hours - $%.1lf - %s)';", i - 1, Supple(cts[dp.path[end][i - 1]].city), Supple(cts[dp.path[end][i - 1]].country), Supple(cts[dp.path[end][i]].city), Supple(cts[dp.path[end][i]].country), Locatert(G, dp.path[end][i - 1], dp.path[end][i])->way, Locatert(G, dp.path[end][i - 1], dp.path[end][i])->time, Locatert(G, dp.path[end][i - 1], dp.path[end][i])->cost, Supple(Locatert(G, dp.path[end][i - 1], dp.path[end][i])->info));
		fprintf(fp, "var path%d = new BMap.Polyline([new BMap.Point(%lf, %lf), new BMap.Point(%lf, %lf)], {strokeColor: '#7b00ff',strokeWeight:7,strokeOpacity:0.8});map.addOverlay(path%d);path%d.addEventListener(\"click\",function(){alert(contentString%02d);});", i - 1, cts[dp.path[end][i - 1]].longitude, cts[dp.path[end][i - 1]].latitude, cts[dp.path[end][i]].longitude, cts[dp.path[end][i]].latitude, i - 1, i - 1,i-1);
	}
	//print the end section
	fprintf(fp, "</script>");
	//close the file
	fclose(fp);
}
