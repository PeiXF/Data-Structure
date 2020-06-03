#include <stdio.h>
#include <stdlib.h>

#define INF 	10000    //代表无限大
#define V_SIZE	11        //景点数

//打印菜单
void printMenu()
{
    printf("\n------------ Scenie Spot Information System ------------\n\n");
    printf("1. Query the shortest way.\n");
    printf("0. Quit System.\n");
    printf("\nPlease input the number of the operation you want to perform: ");
}

//数组填充
void array_fill(int * array, int len, int val)
{
	int i;
	for (i = 0; i < len; i++) {
		array[i] = val;
	}
}

/*
输入参数：
 	graph	权值矩阵
 	n		矩阵大小,即点的个数
 	start	起点
 	dist	接收到所有点的最短距离
*/
void dijkstra(int graph[][V_SIZE], int n, int start, int dist[])
{
	int *path = (int *)malloc(sizeof(int) * n);
	int *shortest = (int *)malloc(sizeof(int) * n);
	int *mark = (int *)malloc(sizeof(int) * n);
	int min, v, i, j;
	array_fill(mark, n, 0);
	array_fill(dist, n, INF);

	for (i = 0; i < n; i++)
	{
		dist[i] = graph[start][i];
		if (i != start && dist[i] < INF)
		{
			path[i] = start;
		}
		else
		{
			path[i] = -1;
		}
	}
	mark[start] = 1;
	while (1)
	{
		min = INF;
		v = -1;
		//找到最小的距离
		for (i = 0; i < n; i++)
		{
			if (!mark[i])
			{
				if (dist[i]<min)
				{
					min = dist[i];
					v = i;
				}
			}
		}
		if (v == -1)
		{
			break; //找不到更短的路径了
		}
		//更新最短路径
		mark[v] = 1;
		for (i = 0; i < n; i++)
		{
			if (!mark[i] && graph[v][i] != INF && dist[v] + graph[v][i] < dist[i])
			{
				dist[i] = dist[v] + graph[v][i];
				path[i] = v;
			}
		}
	}
	//输出路径
	printf("start\tend\tlength\tpath\n");
	for (i = 0; i < n; i++)
	{
		if (i == start) 
		{
			continue;
		}
		array_fill(shortest, n, 0);
		printf("%d\t", start);
		printf("%d\t", i);
		printf("%d\t", dist[i]);
		int k = 0;
		shortest[k] = i;
		while (path[shortest[k]] != start)
		{
			k++;
			shortest[k] = path[shortest[k - 1]];
		}
		k++;
		shortest[k] = start;
		for (j = k; j > 0; j--)
		{
			printf("%d->", shortest[j]);
		}
		printf("%d\n", shortest[0]);
	}
	free(path);
	free(shortest);
	free(mark);
	return;
}

// 1. 求给定起点的最短路径
void shortestWay(int graph[][V_SIZE], int n, int dist[])
{
	int start, end;
	printf("Please input the place you start: ");
	scanf("%d", &start);
	if (start < V_SIZE)
	{
		dijkstra(graph, n, start, dist);
	}
	else
	{
		printf("Place not exist!\n");
	}
	
}

int main()
{
	int operation;
	int dist[V_SIZE];
	int W[V_SIZE][V_SIZE] = {
				{   0,  842,  INF,  INF,  INF,  INF,  511,  INF,  INF,  INF,  INF },

				{ 842,    0,  967,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF },

				{ INF,  967,    0,  607,  902,  INF,  INF,  INF,  INF,  INF,  INF },

				{ INF,  INF,  607,    0,  672,  INF,  INF,  INF,  INF,  INF,  INF },

				{ INF,  INF,  902,  672,    0,  409,  INF,  INF,  INF,  367,  INF },

				{ INF,  INF,  INF,  INF,  409,    0,  534,  INF,  INF,  INF,  INF },

				{ 511,  INF,  INF,  INF,  INF,  534,    0,  349,  INF,  INF,  INF },

				{ INF,  INF,  INF,  INF,  INF,  INF,  349,    0,  651,  INF,  INF },

				{ INF,  INF,  INF,  INF,  INF,  INF,  INF,  651,    0,  825,  INF },

				{ INF,  INF,  INF,  INF,  367,  INF,  INF,  INF,  825,    0,  622 },

				{ INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  622,    0 }};
	while(1)
    {
        printMenu();
        scanf("%d", &operation);
        switch(operation)
        {
            case 0: return 0;
            case 1: shortestWay(W, V_SIZE, dist); break;
        }
        system("pause");
    }
}