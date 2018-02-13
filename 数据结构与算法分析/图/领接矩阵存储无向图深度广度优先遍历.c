#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define LENGTH(s) (sizeof(s)/sizeof(s[0]))

//领接矩阵

typedef struct _graph{
	//顶点集合
	char vetrx[MAX];
	//顶点数
	int vetrxnum;
	//边数
	int edgenum;
	int matrix[MAX][MAX];
}Graph,*pGraph;

//返回s在矩阵中位置
int get_position(Graph g,char s)
{
	int i;
	for(i = 0; i < g.vetrxnum; i++)
	{
		if(g.vetrx[i] == s)
		return i;
	}
	return -1;
}

//返回顶点v的第一个领接点索引，如果没有返回-1
int get_first_vertx(Graph g, int v)
{
	int i;
	if(v < 0 || v > (g.vetrxnum - 1))
	return -1;

	for(i = 0; i < g.vetrxnum; i++)
	{
		if(g.matrix[v][i] == 1)
		return i;
	}
	return -1;
}

//返回顶点v相对于a的下一个领接顶点的索引，没有返回-1
int get_next_vertx(Graph g, int v, int a)
{
	int i;
	if(v < 0 || v > (g.vetrxnum - 1) || a < 0 || a > (g.vetrxnum - 1))
	return -1;

	for(i = a + 1; i < g.vetrxnum; i++)
	{
		if(g.matrix[v][i] == 1)
		return i;
	}

	return -1;
}

//创建图
pGraph create_graph()
{
	//顶点
	char vetrx[] = {'A','B','C','D','E','F','G'};
	//边
	char edge[][2] = {
		{'A','C'},
		{'A','D'},
		{'A','F'},
		{'B','C'},
		{'C','D'},
		{'E','G'},
		{'F','G'},
	};

	int vlen = LENGTH(vetrx);
	int elen = LENGTH(edge);

	int i,p1,p2;
	Graph *pGraph;

	//初始化顶点数和边数
	if((pGraph = (Graph*)malloc(sizeof(Graph))) == NULL)
	{
		return NULL;
	}
	memset(pGraph,0,sizeof(Graph));

	pGraph -> vetrxnum = vlen;
	pGraph -> edgenum = elen;

	//初始化顶点
	for(i = 0; i < pGraph -> vetrxnum; i++)
	{
		pGraph -> vetrx[i] = vetrx[i];
	}

	//初始化边
	for(i = 0; i < pGraph -> edgenum; i++)
	{
		//读取每条边的起点和终点
		p1 = get_position(*pGraph,edge[i][0]);
		p2 = get_position(*pGraph,edge[i][1]);

		//写入领接矩阵
		pGraph -> matrix[p1][p2] = 1;
		pGraph -> matrix[p2][p1] = 1;
	}

	return pGraph;

}


//深度优先遍历图(递归)
void DFS(Graph g, int i, int *visited)
{
	int a;
	visited[i] = 1;
	printf("%c ",g.vetrx[i]);
	//遍历该顶点的所有领接点，如果没有访问过，则继续
	for(a = get_first_vertx(g,i); a >= 0; a = get_next_vertx(g,i,a))
	{
		if(!visited[a])
		DFS(g,a,visited);
	}
}

//深度优先遍历图
void DFSTraverse(Graph g)
{
	int i;
	int visited[MAX];

	//开始时所有顶点都没有被访问
	for(i = 0; i < g.vetrxnum; i++)
	visited[i] = 0;

	printf("DFS: ");
	for(i = 0; i < g.vetrxnum; i++)
	{
		if(!visited[i])
		DFS(g,i,visited);
	}
	printf("\n");
}

//输出图
void print(Graph g)
{
	int i,j;

	printf("Martix Graph:\n");
	for(i = 0; i < g.vetrxnum; i++)
	{
		for(j = 0; j < g.vetrxnum; j++)
		{
			printf("%d ",g.matrix[i][j]);
		}
		printf("\n");
	}
}
int main()
{
	Graph *g;
	p = create_graph();
	print(*g);
	DFSTraverse(*g);
}
