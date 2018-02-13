#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#define MAX 100
#define INF 0X7FFFFFFF
#define LENGTH(a) ((sizeof(a))/sizeof(a[0]))

/*领接矩阵*/
typedef struct _graph {
	char vetrx[MAX];//顶点
	int vetrxnum;//顶点数
	int edgenum;//边数
	int matrix[MAX][MAX];//存储矩阵
}Graph, *pGraph;

/*边数据结构体*/
typedef struct _edgeData {
	char start;//起点
	char end;//终点
	int weight;//权
}EData;

/*创建一个图采用领接矩阵存储并包含权值*/
pGraph create_graph()
{
	char vetrx[] = { 'A','B','C','D','E','F','G' };
	int matrix[][7] = {
		{ 0,    12,   INF, INF, INF, 16, 14 },
		{ 12,   0,    10,  INF, INF, 7, INF },
		{ INF,  10,   0,   3,   5,   6, INF },
		{ INF, INF,   3,   0,   4, INF, INF },
		{ INF, INF,   5,   4,   0,   2,   8 },
		{ 16,   7,   6, INF,   2,   0,   9 },
		{ 14, INF, INF, INF,   8,   9,   0 } 
	};
	int vlen = LENGTH(vetrx);
	int i, j;
	pGraph pG;
	
	//申请空间
	if ((pG = (Graph*)malloc(sizeof(Graph))) == NULL)
		return NULL;
	memset(pG, 0, sizeof(Graph));
	//初始化顶点数
	pG->vetrxnum = vlen;
	//初始化顶点
	for (i = 0; i < pG->vetrxnum; i++)
		pG->vetrx[i] = vetrx[i];

	//初始化边
	for (i = 0; i < pG->vetrxnum; i++)
		for (j = 0; j < pG->vetrxnum; j++)
			pG->matrix[i][j] = matrix[i][j];

	//统计边的数量
	for (i = 0; i < pG->vetrxnum; i++)
		for (j = 0; j < pG->vetrxnum; j++)
			if (i != j && pG->matrix[i][j] != INF)
				pG->edgenum++;

	pG->edgenum /= 2;
	return pG;
}


/*打印输出图*/
void print(Graph g)
{
	int i, j;
	printf("Graph Martix:\n");
	for (i = 0; i < g.vetrxnum; i++)
	{
		for (j = 0; j < g.vetrxnum; j++)
			printf("%10d", g.matrix[i][j]);
		printf("\n");
	}
}

/*获取图中的边的信息*/
EData* get_edge(Graph g)
{
	int i, j;
	int index = 0;
	EData *edge;

	edge = (EData*)malloc(g.edgenum * sizeof(EData));
	for (i = 0; i < g.vetrxnum; i++)
	{
		//因为是无向图，是对称矩阵，所以只遍历上三角位置即可
		for (j = i + 1; j < g.vetrxnum; j++)
		{
			if (g.matrix[i][j] != INF)
			{
				edge[index].start = g.vetrx[i];
				edge[index].end = g.vetrx[j];
				edge[index].weight = g.matrix[i][j];
				index++;
			}
		}
	}
	return edge;
}


/*对图中的边按照权值进行从小到大排序*/
void sort_edge(EData *edge, int len)
{
	int i, j;
	for (i = 0; i < len; i++)
	{
		for (j = i + 1; j < len; j++)
		{
			if (edge[i].weight > edge[j].weight)
			{
				//交换
				EData temp = edge[i];
				edge[i] = edge[j];
				edge[j] = temp;
			}
		}
	}
}

/*获取ch在图的顶点集合中的位置*/
int get_position(Graph g, char ch)
{
	int i;
	for (i = 0; i < g.vetrxnum; i++)
	{
		if (ch == g.vetrx[i])
			return i;
	}
	return -1;
}


/*获取顶点i的终点*/
int get_end(int vends[], int i)
{
	while (vends[i] != 0)
	{
		i = vends[i];
	}
	return i;
}

/*Kruskal算法*/
void kruskal(Graph g)
{
	int i, m, n, p1, p2;
	int length;
	int index = 0;//结果数组result的索引
	int vends[MAX] = { 0 };//新建的最小生成树中的每个顶点对应的终点
	EData result[MAX];//结果数组，即最小生成树中的每条边
	EData *edges;//图中所有的边

	//先获取图中所有的边
	edges = get_edge(g);
	//按照权值对边进行排序
	sort_edge(edges, g.edgenum);

	for (i = 0; i < g.edgenum; i++)
	{
		//获取该边的起点在vertx数组中的索引
		p1 = get_position(g, edges[i].start);
		//终点
		p2 = get_position(g, edges[i].end);
		
		//获取p1，p2在已新建最小生成树中对应的终点，并进行比较
		m = get_end(vends, p1);
		n = get_end(vends, p2);

		//如果m！=n说明边i的起点和终点在已新建的最小生成树中各自对应的终点没有重合，可以作为一条新的边
		if (m != n)
		{
			//构建终点数组，起点为下标，值为终点
			vends[m] = n;
			result[index++] = edges[i];
		}

	}
	free(edges);

	//统计输出最小生成树的信息
	length = 0;
	for (i = 0; i < index; i++)
		length += result[i].weight;
	printf("最小权值为：%d", length);
	printf("\n");
	for (i = 0; i < index; i++)
	{
		printf("%c,%c", result[i].start, result[i].end);
	}
	printf("\n");
	

}
int main()
{
	pGraph g;
	g = create_graph();
	print(*g);
	kruskal(*g);
	system("pause");
	return 0;
}
