#pragma once

#define MVNUM 100  //最大顶点数
#define OK 1

#include<iostream>
using namespace std;

typedef char VerTexType;  //假设顶点的数据类型为字符型
typedef int OtherInfo;    //和边相关的信息

/*-----图的邻接表存储表示-----*/
typedef struct ArcNode {    //边结点
  int adjvex;               //该边所指向的顶点的位置
  struct ArcNode *nextarc;  //指向下一条边的指针
  OtherInfo info;           //和边相关的信息
} ArcNode;

typedef struct VNode {
  VerTexType data;        //顶点信息
  ArcNode *firstarc;      //指向第一条依附该顶点的边的指针
} VNode, AdjList[MVNUM];  // AdjList表示邻接表类型

typedef struct {
  AdjList vertices;  //邻接表
  int vexnum, arcnum;  //图的当前顶点数和边数
} ALGraph;

//算法6.2　采用邻接表表示法创建无向图
int LocateVex(ALGraph G, VerTexType v);
int CreateUDN(ALGraph &G);
void show(ALGraph G);

//算法6.6　采用邻接表表示图的深度优先搜索遍历
void DFS(ALGraph G, int v);