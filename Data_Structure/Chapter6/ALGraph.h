#pragma once

#define MVNUM 100                 //最大顶点数
#define BDNUM MVNUM *(MVNUM - 1)  //最大边数
#define OK 1
#define ERROR 0

#include <iostream>
using namespace std;

typedef char VerTexType;  //假设顶点的数据类型为字符型
typedef int OtherInfo;    //和边相关的信息

/*-----图的邻接表存储表示-----*/
typedef struct ArcNode {    //边结点
  int adjvex;               //该边所指向的顶点的位置
  struct ArcNode *nextarc;  //指向下一条边的指针
  int weight;               //权值
} ArcNode;

typedef struct VNode {
  VerTexType data;        //顶点信息
  ArcNode *firstarc;      //指向第一条依附该顶点的边的指针
} VNode, AdjList[MVNUM];  // AdjList表示邻接表类型

typedef struct {
  AdjList vertices;           //邻接表
  AdjList converse_vertices;  //逆邻接表 算法6.12使用
  int vexnum, arcnum;         //图的当前顶点数和边数
} ALGraph;

//算法6.2　采用邻接表表示法创建无向图
int LocateVex(ALGraph G, VerTexType v);
int CreateUDG(ALGraph &G);
void show(ALGraph G);

//算法6.6　采用邻接表表示图的深度优先搜索遍历
void DFS(ALGraph G, int v);

//算法6.12　拓扑排序
int CreateDG(ALGraph &G);
void FindInDegree(ALGraph G);
int TopoLogicalSort(ALGraph G, int topo[]);

//算法6.13　关键路径算法
int CriticalPath(ALGraph G);