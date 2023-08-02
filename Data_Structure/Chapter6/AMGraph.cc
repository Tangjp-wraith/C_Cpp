#include "AMGraph.h"

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
    if (G.arcs[v][i] && visited[i] == false) {
      return i;
    }
  }
  return -1;
}

int NextAdjVex(AMGraph G, int v, int w) {
  //返回v相对于w的下一个邻接点
  for (int i = w; i < G.vexnum; ++i) {
    if (G.arcs[v][i] && visited[i] == false) {
      return i;
    }
  }
  return -1;
}

void DFS(AMGraph G, int v) {
  //从第v个顶点出发递归地深度优先遍历图G
  cout << G.vexs[v] << " ";
  visited[v] = true;
  for (int w = FistAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
    //依次检查v的所有邻接点w ，FirstAdjVex(G, v)表示v的第一个邻接点
    // NextAdjVex(G, v, w)表示v相对于w的下一个邻接点，w≥0表示存在邻接点
    if (!visited[w]) {
      DFS(G, w);  //对v的尚未访问的邻接顶点w递归调用DFS
    }
  }
}

int main() {
  AMGraph G;
  CreateUDN(G);
  show(G);
  cout << "请输入遍历连通图的起始点：";
  VerTexType c;
  cin >> c;

  int i;
  for (i = 0; i < G.vexnum; ++i) {
    if (c == G.vexs[i]) break;
  }
  while (i >= G.vexnum) {
    cout << "该点不存在,请重新输入！" << endl;
    cout << "请输入遍历连通图的起始点:";
    cin >> c;
    for (i = 0; i < G.vexnum; ++i) {
      if (c == G.vexs[i]) break;
    }
  }
  cout << "深度优先搜索遍历连通图结果:" << endl;
  DFS(G, i);
  cout << endl;
  return 0;
}