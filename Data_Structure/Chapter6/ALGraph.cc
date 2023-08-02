#include "ALGraph.h"

#include <cstddef>
#include <locale>

int LocateVex(ALGraph G, VerTexType v) {
  for (int i = 0; i < G.vexnum; ++i) {
    if (G.vertices[i].data == v) {
      return i;
    }
  }
  return -1;
}
//算法6.2　采用邻接表表示法创建无向图
int CreateUDN(ALGraph &G) {
  //采用邻接表表示法，创建无向图G
  cout << "请输入总顶点数,总边数中间以空格隔开:" << endl;
  cin >> G.vexnum >> G.arcnum;
  cout << "输入点的名称,如 a " << endl;
  for (int i = 0; i < G.vexnum; ++i) {
    cout << "请输入第" << (i + 1) << "个点的名称:" << endl;
    cin >> G.vertices[i].data;
    G.vertices[i].firstarc = NULL;  //初始化表头结点的指针域为NULL
  }
  cout << "请输入一条边依附的顶点,如 a b" << endl;
  for (int k = 0; k < G.arcnum; ++k) {
    VerTexType v1, v2;
    cout << "请输入第" << (k + 1) << "条边依附的顶点:";
    cin >> v1 >> v2;
    //确定v1和v2在G中位置，即顶点在G.vertices中的序号
    int i = LocateVex(G, v1);
    int j = LocateVex(G, v2);
    ArcNode *pos1 = new ArcNode;  //生成一个新的边结点*pos1
    pos1->adjvex = j;             //邻接点序号为j
    pos1->nextarc = G.vertices[i].firstarc;
    G.vertices[i].firstarc = pos1;  //将新结点*pos1插入顶点vi的边表头部
    ArcNode *pos2 = new ArcNode;  //生成另一个对称的新的边结点*pos2
    pos2->adjvex = i;             //邻接点序号为i
    pos2->nextarc = G.vertices[j].firstarc;
    G.vertices[j].firstarc = pos2;  //将新结点*pos2插入顶点vj的边表头部
  }
  return OK;
}

void show(ALGraph G) {
  for (int i = 0; i < G.vexnum; ++i) {
    VNode temp = G.vertices[i];
    ArcNode *pos = temp.firstarc;
    if (!pos) {
      cout << G.vertices[i].data << endl;
    } else {
      cout << temp.data;
      while (pos) {
        cout << "->" << pos->adjvex;
        pos = pos->nextarc;
      }
    }
    cout << endl;
  }
}

int main() {
  ALGraph G;
  CreateUDN(G);
  show(G);
}