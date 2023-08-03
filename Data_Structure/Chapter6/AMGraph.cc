#include "AMGraph.h"

#include <algorithm>

// 算法6.9中辅助数组Edges的定义
struct {
  VerTexType Head;  //边的始点
  VerTexType Tail;  //边的终点
  ArcType lowcost;  //边上的权值
} Edge[(MVNUM * (MVNUM - 1)) / 2];
int Vexset[MVNUM];  //辅助数组Vexset的定义

int LocateVex(AMGraph G, VerTexType v) {
  for (int i = 0; i < G.vexnum; ++i) {
    if (G.vexs[i] == v) {
      return i;
    }
  }
  return -1;
}

//算法6.1　采用邻接矩阵表示法创建无向网
int CreateUDN(AMGraph &G) {
  //采用邻接矩阵表示法，创建无向网G
  cout << "请输入总顶点数,总边数,以空格隔开:" << endl;
  cin >> G.vexnum >> G.arcnum;  //输入总顶点数，总边数
  cout << "输入点的名称,如a" << endl;
  for (int i = 0; i < G.vexnum; ++i) {
    cout << "请输入第" << (i + 1) << "个点的名称:";
    cin >> G.vexs[i];  //依次输入点的信息
  }
  for (int i = 0; i < G.vexnum; ++i) {
    for (int j = 0; j < G.vexnum; ++j) {
      G.arcs[i][j] = MAXINT;
    }
  }
  cout << "输入边依附的顶点及权值,如 a b 5" << endl;
  for (int k = 0; k < G.arcnum; ++k) {
    VerTexType v1, v2;
    ArcType w;
    cout << "请输入第" << (k + 1) << "条边依附的顶点及权值:";
    cin >> v1 >> v2 >> w;
    int i = LocateVex(G, v1);
    int j = LocateVex(G, v2);
    G.arcs[i][j] = w;
    G.arcs[j][i] = w;

    // 算法6.9　克鲁斯卡尔算法
    Edge[k].lowcost = w;
    Edge[k].Head = v1;
    Edge[k].Tail = v2;
  }
  return OK;
}

void show(AMGraph G) {
  for (int i = 0; i < G.vexnum; ++i) {
    for (int j = 0; j < G.vexnum; ++j) {
      if (j != G.vexnum - 1) {
        if (G.arcs[i][j] != MAXINT) {
          cout << G.arcs[i][j] << "\t";
        } else {
          cout << "∞"
               << "\t";
        }
      } else {
        if (G.arcs[i][j] != MAXINT) {
          cout << G.arcs[i][j] << endl;
        } else {
          cout << "∞" << endl;
        }
      }
    }
  }
}

bool visited[MVNUM];
int FistAdjVex(AMGraph G, int v) {
  //返回v的第一个邻接点
  for (int i = 0; i < G.vexnum; ++i) {
    if (G.arcs[v][i] != MAXINT && visited[i] == false) {
      return i;
    }
  }
  return -1;
}

int NextAdjVex(AMGraph G, int v, int w) {
  //返回v相对于w的下一个邻接点
  for (int i = w; i < G.vexnum; ++i) {
    if (G.arcs[v][i] != MAXINT && visited[i] == false) {
      return i;
    }
  }
  return -1;
}

//算法6.3/6.5　深度优先搜索遍历连通图的递归算法
void DFS(AMGraph G, int v) {
  //从第v个顶点出发递归地深度优先遍历图G
  cout << G.vexs[v] << " ";
  visited[v] = true;
  int w;
  for (w = FistAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
    //依次检查v的所有邻接点w ，FirstAdjVex(G, v)表示v的第一个邻接点
    // NextAdjVex(G, v, w)表示v相对于w的下一个邻接点，w≥0表示存在邻接点
    if (!visited[w]) {
      DFS(G, w);  //对v的尚未访问的邻接顶点w递归调用DFS
    }
  }
}

//算法6.4　深度优先搜索遍历非连通图
void DFSTraverse(AMGraph G) {
  for (int v = 0; v < G.vexnum; ++v) {
    visited[v] = false;
  }
  for (int v = 0; v < G.vexnum; ++v) {
    if (!visited[v]) {
      DFS(G, v);
    }
  }
}

//算法6.7　广度优先搜索遍历连通图
void BFS(AMGraph G, int v) {
  queue<int> que;
  cout << G.vexs[v] << " ";
  visited[v] = true;
  que.push(v);
  ArcType w;
  while (!que.empty()) {
    ArcType u = que.front();
    for (w = FistAdjVex(G, v); w >= 0; w = NextAdjVex(G, u, w)) {
      if (!visited[w]) {
        cout << G.vexs[w] << " ";
        visited[w] = true;
        que.push(w);
      }
    }
  }
}

//算法6.8　普里姆算法
//辅助数组的定义，用来记录从顶点集U到V-U的权值最小的边
struct {
  VerTexType adjvex;  //最小边在U中的那个顶点
  ArcType lowcost;    //最小边上的权值
} closedge[MVNUM];

int Min(AMGraph G) {
  //返回权值最小的点
  int index = -1;
  int minx = MAXINT;
  for (int i = 0; i < G.vexnum; ++i) {
    if (minx > closedge[i].lowcost && closedge[i].lowcost) {
      minx = closedge[i].lowcost;
      index = i;
    }
  }
  return index;
}

void MiniSpanTree_Prim(AMGraph G, VerTexType u) {
  //无向网G以邻接矩阵形式存储，从顶点u出发构造G的最小生成树T，输出T的各条边
  int pos = LocateVex(G, u);
  for (int i = 0; i < G.vexnum; ++i) {  //对V-U的每一个顶点vi，初始化closedge[i]
    if (i != pos) {
      closedge[i].adjvex = u;
      closedge[i].lowcost = G.arcs[pos][i];
    }
  }
  closedge[pos].lowcost = 0;  //初始，U = {u}
  for (int i = 1; i < G.vexnum; ++i) {
    //选择其余n-1个顶点，生成n-1条边(n= G.vexnum)
    pos = Min(G);
    //求出T的下一个结点：第pos个顶点，closedge[pos]中存有当前最小边
    VerTexType u0 = closedge[pos].adjvex;  // u0为最小边的一个顶点，u0∈U
    VerTexType v0 = G.vexs[pos];  // v0为最小边的另一个顶点，v0∈V-U
    cout << "边  " << u0 << "--->" << v0 << endl;
    closedge[pos].lowcost = 0;  //第k个顶点并入U集
    for (int i = 0; i < G.vexnum; ++i) {
      if (G.arcs[pos][i] < closedge[i].lowcost) {  //新顶点并入U后重新选择最小边
        closedge[i].adjvex = G.vexs[pos];
        closedge[i].lowcost = G.arcs[pos][i];
      }
    }
  }
}

//算法6.9　克鲁斯卡尔算法

//----------冒泡排序-------------------
void Sort(AMGraph G) {
  int m = G.arcnum - 2;
  int flag = 1;
  while ((m > 0) && flag == 1) {
    flag = 0;
    for (int j = 0; j <= m; j++) {
      if (Edge[j].lowcost > Edge[j + 1].lowcost) {
        flag = 1;

        VerTexType temp_Head = Edge[j].Head;
        Edge[j].Head = Edge[j + 1].Head;
        Edge[j + 1].Head = temp_Head;

        VerTexType temp_Tail = Edge[j].Tail;
        Edge[j].Tail = Edge[j + 1].Tail;
        Edge[j + 1].Tail = temp_Tail;

        ArcType temp_lowcost = Edge[j].lowcost;
        Edge[j].lowcost = Edge[j + 1].lowcost;
        Edge[j + 1].lowcost = temp_lowcost;
      }  // if
    }    // for
    --m;
  }  // while
}  // Sort

void MiniSpanTree_Kruskal(AMGraph G) {
  //无向网G以邻接矩阵形式存储，构造G的最小生成树T，输出T的各条边
  Sort(G);  //将数组Edge中的元素按权值从小到大排序
  for (int i = 0; i < G.vexnum; ++i) {
    Vexset[i] = i;  //辅助数组，表示各顶点自成一个连通分量
  }
  for (int i = 0; i < G.vexnum; ++i) {
    //依次查看排好序的数组Edge中的边是否在同一连通分量上
    int v1 = LocateVex(G, Edge[i].Head);  // v1为边的始点Head的下标
    int v2 = LocateVex(G, Edge[i].Tail);  // v2为边的终点Tail的下标
    int vs1 = Vexset[v1];  //获取边Edge[i]的始点所在的连通分量vs1
    int vs2 = Vexset[v2];
    if (vs1 != vs2) {  //边的两个顶点分属不同的连通分量
      cout << Edge[i].Head << "-->" << Edge[i].Tail << endl;  //输出此边
      //合并vs1和vs2两个分量，即两个集合统一编号
      for (int j = 0; j < G.vexnum; ++j) {
        if (Vexset[j] == vs2) {
          Vexset[j] = vs1;  //集合编号为vs2的都改为vs1
        }
      }
    }
  }
}

//算法6.10　迪杰斯特拉算法

int *Dij = new int[MVNUM];     //用于记录最短路的长度
bool *S = new bool[MVNUM];   //标记顶点是否进入S集合
int *Path_DIJ = new int[MVNUM];  //用于记录最短路顶点的前驱

// 创建有向图
int CreateDN(AMGraph &G) {
  //采用邻接矩阵表示法，创建有向网G
  cout << "请输入总顶点数,总边数,以空格隔开:" << endl;
  cin >> G.vexnum >> G.arcnum;  //输入总顶点数，总边数
  cout << "输入点的名称,如a" << endl;
  for (int i = 0; i < G.vexnum; ++i) {
    cout << "请输入第" << (i + 1) << "个点的名称:";
    cin >> G.vexs[i];  //依次输入点的信息
  }
  for (int i = 0; i < G.vexnum; ++i) {
    for (int j = 0; j < G.vexnum; ++j) {
      G.arcs[i][j] = MAXINT;
    }
  }
  cout << "输入边依附的顶点及权值,如 a b 5" << endl;
  for (int k = 0; k < G.arcnum; ++k) {
    VerTexType v1, v2;
    ArcType w;
    cout << "请输入第" << (k + 1) << "条边依附的顶点及权值:";
    cin >> v1 >> v2 >> w;
    int i = LocateVex(G, v1);
    int j = LocateVex(G, v2);
    G.arcs[i][j] = w;
  }
  return OK;
}

void ShortestPath_DIJ(AMGraph G, int v0) {
  //用Dijkstra算法求有向网G的v0顶点到其余顶点的最短路径
  int n = G.vexnum;  // n为G中顶点的个数
  int minx, v;
  for (int v = 0; v < n; ++v) {
    S[v] = false;
    Dij[v] = G.arcs[v0][v];  //将v0到各个终点的最短路径长度初始化为弧上的权值
    if (Dij[v < MAXINT]) {
      Path_DIJ[v] = v0;  //如果v0和v之间有弧，则将v的前驱置为v0
    } else {
      Path_DIJ[v] = -1;  //如果v0和v之间无弧，则将v的前驱置为-1
    }
  }
  S[v0] = true;  //将v0加入S
  Dij[v0] = 0;     //源点到源点的距离为0
  /*―初始化结束，开始主循环，每次求得v0到某个顶点v的最短路径，将v加到S集―*/
  for (int i = 1; i < n; ++i) {  //对其余n-1个顶点，依次进行计算
    minx = MAXINT;
    for (int w = 0; w < n; ++w) {
      if (!S[w] && Dij[w] < minx) {  //选择一条当前的最短路径，终点为v
        v = w;
        minx = Dij[w];
      }
    }
    S[v] = true;  //将v加入S
    //更新从v0出发到集合V?S上所有顶点的最短路径长度
    for (int w = 0; w < n; ++w) {
      if (!S[w] && (Dij[v] + G.arcs[v][w] < Dij[w])) {
        Dij[w] = Dij[v] + G.arcs[v][w];  //更新D[w]
        Path_DIJ[w] = v;                 //更改w的前驱为v
      }
    }
  }
}

void DisplayPath_DIJ(AMGraph G, int begin, int temp) {
  if (Path_DIJ[temp] != -1) {
    DisplayPath_DIJ(G, begin, Path_DIJ[temp]);
    cout << G.vexs[Path_DIJ[temp]] << "-->";
  }
}



int main() {
  AMGraph G;

  // CreateUDN(G);
  // show(G);

  // cout << "请输入遍历连通图的起始点：";
  // VerTexType c;
  // cin >> c;
  // int i;
  // for (i = 0; i < G.vexnum; ++i) {
  //   if (c == G.vexs[i]) break;
  // }
  // while (i >= G.vexnum) {
  //   cout << "该点不存在,请重新输入!" << endl;
  //   cout << "请输入遍历连通图的起始点:";
  //   cin >> c;
  //   for (i = 0; i < G.vexnum; ++i) {
  //     if (c == G.vexs[i]) break;
  //   }
  // }
  // cout << "遍历连通图结果:" << endl;
  // DFS(G, i);
  // BFS(G, i);
  // cout << endl;

  // DFSTraverse(G);
  // cout << endl;

  // MiniSpanTree_Prim(G, 'a');
  // cout << endl;

  // MiniSpanTree_Kruskal(G);

  int num_start, num_destination;
  VerTexType start, destination;
  CreateDN(G);
  cout << "请依次输入起始点,终点名称:";
  cin >> start >> destination;
  num_start = LocateVex(G, start);
  num_destination = LocateVex(G, destination);
  ShortestPath_DIJ(G, num_start);
  cout << endl << "最短路径为:";
  DisplayPath_DIJ(G, num_start, num_destination);
  cout << G.vexs[num_destination] << endl;

  return 0;
}