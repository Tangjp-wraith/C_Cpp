#pragma once
#include <iostream>
#include <queue>

using namespace std;

#define MAXINT 32767  //表示极大值，即∞
#define MVNUM 100     //最大顶点数
#define OK 1

typedef char VerTexType;  //假设顶点的数据类型为字符型
typedef int ArcType;      //假设边的权值类型为整型

/*-----图的邻接矩阵存储表示-----*/
typedef struct {
  VerTexType vexs[MVNUM];      //顶点表
  ArcType arcs[MVNUM][MVNUM];  //邻接矩阵
  int vexnum, arcnum;          //图的当前点数和边数
} AMGraph;

//算法6.1　采用邻接矩阵表示法创建无向网
int LocateVex(AMGraph G, VerTexType v);
int CreateUDN(AMGraph &G);
void show(AMGraph G);

//算法6.3/6.5 深度优先搜索遍历连通图的递归算法
int FistAdjVex(AMGraph G, int v);
int NextAdjVex(AMGraph G, int v, int w);
void DFS(AMGraph G, int v);

//算法6.4　深度优先搜索遍历非连通图
void DFSTraverse(AMGraph G);

//算法6.7　广度优先搜索遍历连通图
void BFS(AMGraph G, int v);

//算法6.8　普里姆算法
int Min(AMGraph G);
void MiniSpanTree_Prim(AMGraph G, VerTexType u);

//算法6.9　克鲁斯卡尔算法
void MiniSpanTree_Kruskal(AMGraph G);

//算法6.10　迪杰斯特拉算法
int CreateDN(AMGraph &G);
void ShortestPath_DIJ(AMGraph G, int v0);
void DisplayPath_DIJ(AMGraph G, int begin, int temp);

//算法6.11　弗洛伊德算法
void ShortestPath_Floyed(AMGraph G);
void DisplayPath_Floyed(AMGraph G, int begin, int temp);
