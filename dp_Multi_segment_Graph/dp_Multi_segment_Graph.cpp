// dp_Multi_segment_Graph.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#define INFINITY INT_MAX
//#define VERTEX_NUM 10
//#define STRING_LEN 20
////建立存储方式为邻接表的图
//typedef char* VertexType;
////定义弧
//typedef struct Arc {
//	int j;
//	struct Arc* next;
//	int weight;			//弧的权重
//};
//typedef struct Vertex{
//	VertexType v;
//	Arc* list;
//}AdjList[VERTEX_NUM];
//typedef struct AGraph {
//	AdjList vexs;
//	int vexnum, arcnum;
//};
//int GetVertex(AGraph*G,VertexType u) {
//	for (int i = 0; i < G->vexnum; i++) {
//		if (strcmp(G->vexs[i].v, u) == 0)
//			return i;
//	}
//	return -1;
//}
//void InsertArc(AGraph* G,int v,int w,int weight) {
//	//插入弧
//	//生成一条弧
//	Arc* a,*tmp;
//	a = (Arc*)malloc(sizeof(Arc));
//	a->j = w;
//	a->weight = weight;
//	a->next = NULL;
//	tmp = G->vexs[v].list;
//	if (tmp) {
//		while (tmp->next) {
//			tmp = tmp->next;
//		}
//		tmp->next = a;
//	}
//	else {
//		G->vexs[v].list = a;//一定要直接对结构体赋值,而不是对tmp这个临时指针
//	}
//}
//AGraph CreateGraph(AGraph*G) {
//	int n, m;
//	printf("请输入顶点数:\n");
//	scanf_s("%d", &n);
//	printf("请输入路径数:\n");
//	scanf_s("%d",&m);
//	G->vexnum = n;
//	G->arcnum = m;
//	int i, j1, j2,w;
//	char* nam,*n1,*n2;
//	for (i = 0; i < G->vexnum; i++) {
//		printf("请输入顶点名:\n");
//		nam = (char*)malloc(STRING_LEN*sizeof(char));
//		scanf_s("%s", nam, sizeof(nam));
//		G->vexs[i].v = nam;
//		G->vexs[i].list = NULL;
//	}
//	for (i = 0; i < G->arcnum; i++) {
//		printf("请输入起点和终点:\n");
//		n1 = (char*)malloc(sizeof(char) * STRING_LEN);
//		n2 = (char*)malloc(sizeof(char) * STRING_LEN);
//		scanf_s("%s", n1, sizeof(n1));
//		scanf_s("%s", n2, sizeof(n2));
//		printf("请输入这条弧的权重:\n");
//		scanf_s("%d",&w);
//		j1 = GetVertex(G,n1);
//		j2 = GetVertex(G,n2);
//		if (j1 >= 0 && j2 >= 0) {
//			InsertArc(G,j1,j2,w);
//		}
//	}
//	return *G;
//}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINITY INT_MAX
#define VERTEX_NUM 100				//图节点个数最大值,尽可能设大一点,防止溢出
#define STRING_LEN 1
//建立存储方式为邻接矩阵的图
typedef struct VertexType {
	int nam;
};
typedef struct Arc {
	bool flag;						//标志是否已被访问
	int weight;
}arc[VERTEX_NUM][VERTEX_NUM];
typedef struct AGraph {
	VertexType vexs[VERTEX_NUM];
	arc arcs;						//定义邻接矩阵
	int vexnum, arcnum;
	int segment;					//段数
};
void InsertArc(AGraph * G,int v, int w, int weight) {
	G->arcs[v][w].weight = weight;
	printf("G->arcs[%d][%d].weight=%d\n",v,w, G->arcs[v][w].weight);
}
AGraph CreateGraph(AGraph * G) {
	int n, m,s;
	printf("请输入顶点数:\n");
	scanf_s("%d", &n);
	printf("请输入路径数:\n");
	scanf_s("%d", &m);
	printf("请输入段数:\n");
	scanf_s("%d", &s);
	G->vexnum = n;
	G->arcnum = m;
	G->segment = s;
	//G->vexnum = 12;
	//G->arcnum = 20;
	//G->segment = 5;
	int i, j, w, n1, n2;
	for (i = 0; i < G->vexnum; i++) {
		for (j = 0; j < G->vexnum; j++) {
			G->arcs[i][j].weight = INFINITY;
			G->arcs[i][j].flag = false;
		}
	}
	//InsertArc(G, 0, 1, 9);//测试用
	//InsertArc(G, 0, 2, 7);
	//InsertArc(G, 0, 3, 3);
	//InsertArc(G, 0, 4, 2);
	//InsertArc(G, 1, 5, 4);
	//InsertArc(G, 1, 6, 2);
	//InsertArc(G, 1, 7, 1);
	//InsertArc(G, 2, 5, 2);
	//InsertArc(G, 2, 6, 7);
	//InsertArc(G, 3, 7, 11);
	//InsertArc(G, 4, 6, 11);
	//InsertArc(G, 4, 7, 8);
	//InsertArc(G, 5, 8, 6);
	//InsertArc(G, 5, 9, 5);
	//InsertArc(G, 6, 8, 4);
	//InsertArc(G, 6, 9, 3);
	//InsertArc(G, 7, 9, 5);
	//InsertArc(G, 7, 10, 6);
	//InsertArc(G, 8, 11, 4);
	//InsertArc(G, 9, 11, 2);
	//InsertArc(G, 10, 11, INFINITY);
	printf("请输入对应弧的起点,终点,权重:\n");
	for (i = 0; i < G->arcnum; i++) {
		scanf_s("%d%d%d", &n1, &n2, &w);
		InsertArc(G, n1, n2, w);
	}
	return *G;
}
int NextArc(AGraph*G,int i) {
	//i表示起点,返回终点j
	int j;
	for (j = 0; j < G->vexnum; j++) {
		if (j != i) {
			if (G->arcs[i][j].weight != INFINITY && (!G->arcs[i][j].flag)) {
				G->arcs[i][j].flag = true;
				return j;
			}
		}
	}
	return -1;
}
void print(AGraph*G,int*d) {
	int i;
	printf("最短路径为:");
	printf("%d", d[0]);
	for (i = 1; i < G->segment; i++) {
		printf("->%d", d[i]);
	}
	printf("\n");
}
void DP_Multi_Graph(AGraph*G) {
	int *cost,*d;				
	cost = (int*)malloc(sizeof(int) * G->vexnum-1);
	d = (int*)malloc(sizeof(int) * G->vexnum-1);					//d保存最短路径的解
	int i,j;
	for (i = 0; i < G->vexnum; i++) {
		cost[i] = 0;
	}
	
	for (i = G->vexnum-1; i >= 0; i--) {
		cost[i] = INFINITY;
		for (j = NextArc(G, i); j >= 0; j = NextArc(G, i)) {
			if (j == G->vexnum - 1) {
				cost[i] = G->arcs[i][j].weight;
				d[i] = j;
			}
			else {
				if ((cost[j] + G->arcs[i][j].weight)> 0 &&cost[j] + G->arcs[i][j].weight < cost[i]) {
					//(cost[j] + G->arcs[i][j].weight)> 0 加入此判断条件,防止溢出后数据变为负数后,影响结果
					cost[i] = cost[j] + G->arcs[i][j].weight;
					d[i] = j;
				}
			}
		}	
	}
	int* p;
	p = (int*)malloc(sizeof(int) * G->segment);
	p[0] = 0; p[G->segment-1] = G->vexnum - 1;
	for (i = 1; i < G->segment - 1; i++) {
		p[i] = d[p[i - 1]];
	}
	print(G, p);
}
int main()
{
	AGraph G;
	G = CreateGraph(&G);
	DP_Multi_Graph(&G);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
