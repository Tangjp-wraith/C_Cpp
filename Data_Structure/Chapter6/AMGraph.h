#pragma once
#include <iostream>

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

//算法6.3　深度优先搜索遍历连通图的递归算法
int FistAdjVex(AMGraph G,int v);
int NextAdjVex(AMGraph G, int v,int w);
void DFS(AMGraph G,int v);
