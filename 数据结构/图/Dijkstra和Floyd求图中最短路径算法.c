#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <malloc.h>


#define MAX 100
#define INF 8888
#define LENGTH(a)   (sizeof(a)/sizeof(a[0]))

/*领接矩阵即城市网络图的结构体*/
typedef struct _graph {
	char *city[MAX];//城市集合即顶点集合
	int vertxnum;//顶点数
	int edgenum;//边数
	int martix[MAX][MAX];
}Graph, *pGraph;

/*边的结构体，包括每条边的路径长度*/
typedef struct _edgeData {
	char start;//边起点
	char end;//终点
	int distance;//边长度
}EData;


/*创建城市网络图*/
pGraph create_graph()
{
	char *city[] = {"太原","大同","北京","北欧","天津","上海","重庆"};
	int martix[][9] = {
		{ 0,  120, INF, INF, INF,  1644,  1466 },
		{ 120,   0,  104, INF, INF,   787, INF },
		{ INF,  104,   0,   354,   555,   666, INF },
		{ INF, INF,   354,   0,   465, INF, INF },
		{ INF, INF,   555,   465,   0,   265,   880 },
		{ 1644,   787,   666, INF,   265,   0,   943 },
		{ 1466, INF, INF, INF,   880,   943,   0 } 
	};
	int vlen = LENGTH(city);
	int i, j;


	Graph* pG;

	// 开辟空间
	if ((pG = (Graph*)malloc(sizeof(Graph))) == NULL)
		return NULL;
	memset(pG, 0, sizeof(Graph));
	
	//初始化顶点数和顶点
	pG->vertxnum = vlen;
	for (i = 0; i < pG->vertxnum; i++)
		pG->city[i] = city[i];

	//初始化边
	for (i = 0; i < pG->vertxnum; i++)
		for (j = 0; j < pG->vertxnum; j++)
			pG->martix[i][j] = martix[i][j];

	//统计边的数目
	for (i = 0; i < pG->vertxnum; i++)
		for (j = 0; j < pG->vertxnum; j++)
			if (i != j && pG->martix[i][j] != INF)
				pG->edgenum++;
	//有向图为对称矩阵
	pG->edgenum /= 2;
	return pG;
}


/*输出城市网络图*/
void print_graph(Graph g)
{
	int i, j;
	printf("城市网络图:\n");
	for (i = 0; i < g.vertxnum; i++)
	{
		printf("%s ", g.city[i]);
		for (j = 0; j < g.vertxnum; j++)
			printf("%5d", g.martix[i][j]);
		printf("\n");
	}
	printf("城市网络图构建成功...\n");
}

/*Dijkstra最短路径*/
/*bao为起点，prev[]为前驱顶点，dist[]为起点bao到其他顶点的最小路径*/
void dijkstra(Graph g, int bao, int prev[], int dist[])
{
	int i, j, k;
	int min;
	int temp;
	int flag[MAX];//flag[i]=1表示顶点bao到顶点i已存在最短路径
	
	//初始化
	for (i = 0; i < g.vertxnum; i++)
	{
		flag[i] = 0;//顶点的最短路径都未获取
		prev[i] = 0;//顶点的前驱都未获取
		dist[i] = g.martix[bao][i];//顶点的最短路径最后都为起点bao到i的权值
	}

	//初始化起点bao
	flag[bao] = 1;
	dist[bao] = 1;

	//遍历顶点，每次找出一个顶点的最短路径
	for (i = 1; i < g.vertxnum; i++)
	{
		//寻找距离起点bao的最小路径的顶点k
		min = INF;
		for (j = 0; j < g.vertxnum; j++)
		{
			if (flag[j] == 0 && dist[j] < min)
			{
				min = dist[j];
				k = j;
			}
		}

		//记录k为当前最小路径顶点
		flag[k] = 1;

		//核心部分
		//更新未获取最小路径的顶点与起点bao的距离和前驱顶点
		for (j = 0; j < g.vertxnum; j++)
		{
			temp = (g.martix[k][j] == INF ? INF : (g.martix[k][j] + min));
			if (flag[j] == 0 && temp < dist[j])
			{
				dist[j] = temp;
				prev[j] = k;
			}
		}
	}

	//输出最小路径信息
	printf("目标城市：%s\n", g.city[bao]);
	for (i = 0; i < g.vertxnum; i++)
	{
		printf("最小路径(%s,%s)为：%d\n", g.city[bao], g.city[i], dist[i]);
	}
}


void floyd(Graph g, int path[][MAX], int dist[][MAX])
{
	int i, j, k;
	int tmp;

	// 初始化
	for (i = 0; i < g.vertxnum; i++)
	{
		for (j = 0; j < g.vertxnum; j++)
		{
			dist[i][j] = g.martix[i][j];    // "顶点i"到"顶点j"的路径长度为"i到j的权值"。
			path[i][j] = j;                 // "顶点i"到"顶点j"的最短路径是经过顶点j。
		}
	}

	// 计算最短路径
	for (k = 0; k < g.vertxnum; k++)
	{
		for (i = 0; i < g.vertxnum; i++)
		{
			for (j = 0; j < g.vertxnum; j++)
			{
				//更新dist[i][j]和path[i][j]
				tmp = (dist[i][k] == INF || dist[k][j] == INF) ? INF : (dist[i][k] + dist[k][j]);
				if (dist[i][j] > tmp)
				{
				
					dist[i][j] = tmp;
					path[i][j] = path[i][k];
				}
			}
		}
	}

	// 打印floyd最短路径的结果
	printf("最小路径为: \n");
	for (i = 0; i < g.vertxnum; i++)
	{
		for (j = 0; j < g.vertxnum; j++)
			printf("%2d  ", dist[i][j]);
		printf("\n");
	}
}


int main()
{
	Graph *g = create_graph();
	print_graph(*g);
	int prev[MAX] = { 0 };
	int dist[MAX] = { 0 };
	int path[MAX][MAX] = { 0 };   
	int floy[MAX][MAX] = { 0 };   

	dijkstra(*g, 2, prev, dist);

	floyd(*g, path, floy);
	system("pause");
	return 0;
}
