#include "ALGraph.h"

#include <cstddef>
#include <locale>
#include <stack>

int LocateVex(ALGraph G, VerTexType v) {
  for (int i = 0; i < G.vexnum; ++i) {
    if (G.vertices[i].data == v) {
      return i;
    }
  }
  return -1;
}
//算法6.2　采用邻接表表示法创建无向图
int CreateUDG(ALGraph &G) {
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

//算法6.6　采用邻接表表示图的深度优先搜索遍历
bool visited[MVNUM];
void DFS(ALGraph G, int v) {
  cout << G.vertices[v].data << " ";
  visited[v] = true;
  ArcNode *pos = G.vertices[v].firstarc;
  while (pos) {
    int w = pos->adjvex;
    if (!visited[w]) {
      DFS(G, w);
    }
    pos = pos->nextarc;
  }
}

//算法6.12　拓扑排序
int indegree[MVNUM];  //数组indegree存放个顶点的入度
stack<int> st;

int CreateDG(ALGraph &G) {
  //创建有向图G的邻接表、逆邻接表
  cout << "请输入总顶点数,总边数,以空格隔开:";
  cin >> G.vexnum >> G.arcnum;  //输入总顶点数，总边数
  cout << "输入点的名称,如a" << endl;
  for (int i = 0; i < G.vexnum; ++i) {  //输入各点，构造表头结点表
    cout << "请输入第" << (i + 1) << "个点的名称:";
    cin >> G.vertices[i].data;
    G.converse_vertices[i].data = G.vertices[i].data;
    //初始化表头结点的指针域为NULL
    G.vertices[i].firstarc = NULL;
    G.converse_vertices[i].firstarc = NULL;
  }
  cout << "输入边依附的顶点,如a b" << endl;
  for (int k = 0; k < G.arcnum; ++k) {
    VerTexType v1, v2;
    int w;
    cout << "请输入第" << (k + 1) << "条边依附的顶点:";
    cin >> v1 >> v2 >> w;
    //确定v1和v2在G中位置，即顶点在G.vertices中的序号
    int i = LocateVex(G, v1);
    int j = LocateVex(G, v2);
    ArcNode *pos1 = new ArcNode;  //生成一个新的边结点*pos1
    //将新结点*p1插入顶点vi的边表头部
    pos1->adjvex = j;  //邻接点序号为j
    pos1->nextarc = G.vertices[i].firstarc;
    G.vertices[i].firstarc = pos1;
    pos1->weight = w;
    ArcNode *pos2 = new ArcNode;
    pos2->adjvex = i;
    pos2->nextarc = G.converse_vertices[j].firstarc;
    G.converse_vertices[j].firstarc = pos2;
    pos2->weight = w;
  }
  return OK;
}

void FindInDegree(ALGraph G) {
  //求出各顶点的入度存入数组indegree中
  for (int i = 0; i < G.vexnum; ++i) {
    int cnt = 0;
    ArcNode *pos = G.converse_vertices[i].firstarc;
    while (pos) {
      pos = pos->nextarc;
      ++cnt;
    }
    indegree[i] = cnt;
  }
}

int TopoLogicalSort(ALGraph G, int topo[]) {
  //有向图G采用邻接表存储结构
  //若G无回路，则生成G的一个拓扑序列topo[]并返回OK，否则ERROR
  FindInDegree(G);
  for (int i = 0; i < G.vexnum; ++i) {
    if (!indegree[i]) {
      st.push(i);  //入度为0者进栈
    }
  }
  int m = 0;  //对输出顶点计数，初始为0
  while (!st.empty()) {
    int i = st.top();  //将栈顶顶点vi出栈
    st.pop();
    topo[m] = i;  //将vi保存在拓扑序列数组topo中
    ++m;
    // pos指向vi的第一个邻接点
    ArcNode *pos = G.vertices[i].firstarc;
    while (pos) {
      int k = pos->adjvex;  // vk为vi的邻接点
      --indegree[k];        // vi的每个邻接点的入度减1
      if (!indegree[k]) {   //若入度减为0，则入栈
        st.push(k);
      }
      pos = pos->nextarc;  // pos指向顶点vi下一个邻接结点
    }
  }
  if (m < G.vexnum) {  //该有向图有回路
    return ERROR;
  }
  return OK;
}

//算法6.13　关键路径算法
int ve[BDNUM];    //事件vi的最早发生时间
int vl[BDNUM];    //事件vi的最迟发生时间
int topo[MVNUM];  //记录拓扑序列的顶点序号

int CriticalPath(ALGraph G) {
  // G为邻接表存储的有向网，输出G的各项关键活动
  if (!TopoLogicalSort(G, topo)) {
    return ERROR;
  }
  int n = G.vexnum;
  for (int i = 0; i < n; ++i) {
    ve[i] = 0;  //给每个事件的最早发生时间置初值0
  }
  //按拓扑次序求每个事件的最早发生时间
  for (int i = 0; i < n; ++i) {
    int k = topo[i];  //取得拓扑序列中的顶点序号k
    ArcNode *pos = G.vertices[k].firstarc;  // p指向k的第一个邻接顶点
    while (pos) {  //依次更新k的所有邻接顶点的最早发生时间
      int j = pos->adjvex;                // j为邻接顶点的序号
      if (ve[j] < ve[k] + pos->weight) {  //更新顶点j的最早发生时间ve[j]
        ve[j] = ve[k] + pos->weight;
      }
      pos = pos->nextarc;  // p指向k的下一个邻接顶点
    }
  }
  for (int i = 0; i < n; ++i) {  //给每个事件的最迟发生时间置初值ve[n-1]
    vl[i] = ve[n - 1];
  }
  // 按逆拓扑次序求每个事件的最迟发生时间
  for (int i = n - 1; i >= 0; --i) {
    int k = topo[i];  //取得拓扑序列中的顶点序号k
    ArcNode *pos = G.vertices[k].firstarc;  // p指向k的第一个邻接顶点
    while (pos) {           //根据k的邻接点，更新k的最迟发生时间
      int j = pos->adjvex;  // j为邻接顶点的序号
      if (vl[k] > vl[j] - pos->weight) {  //更新顶点k的最迟发生时间vl[k]
        vl[k] = vl[j] - pos->weight;
      }
      pos = pos->nextarc;  // p指向k的下一个邻接顶点
    }
  }
  //判断每一活动是否为关键活动
  cout << "关键活动路径为:";
  for (int i = 0; i < n; ++i) {  //每次循环针对vi为活动开始点的所有活动
    ArcNode *pos = G.vertices[i].firstarc;  // p指向i的第一个邻接顶点
    while (pos) {
      int j = pos->adjvex;          // j为i的邻接顶点的序号
      int e = ve[i];                //计算活动<vi, vj>的最早开始时间
      int l = vl[j] - pos->weight;  //计算活动<vi, vj>的最迟开始时间
      if (e == l) {                 //若为关键活动，则输出<vi, vj>
        cout << G.vertices[i].data << "-->" << G.vertices[j].data << " ";
      }
      pos = pos->nextarc;  // p指向i的下一个邻接顶点
    }
  }
  cout << endl;
  return OK;
}

int main() {
  ALGraph G;

  // CreateUDG(G);
  // show(G);

  // cout << "请输入遍历连通图的起始点：";
  // VerTexType c;
  // cin >> c;
  // int i;
  // for (i = 0; i < G.vexnum; ++i) {
  //   if (c == G.vertices[i].data) break;
  // }
  // while (i >= G.vexnum) {
  //   cout << "该点不存在,请重新输入!" << endl;
  //   cout << "请输入遍历连通图的起始点:";
  //   cin >> c;
  //   for (i = 0; i < G.vexnum; ++i) {
  //     if (c == G.vertices[i].data) break;
  //   }
  // }
  // cout << "深度优先搜索遍历图结果:" << endl;
  // DFS(G, i);
  // cout << endl;

  CreateDG(G);
  cout << "有向图的邻接表,逆邻接表创建完成!" << endl;
  // int *topo = new int[G.vexnum];
  // if (TopoLogicalSort(G, topo)) {
  //   cout << "该有向图的拓扑有序序列为：";
  //   for (int j = 0; j < G.vexnum; j++) {
  //     if (j != G.vexnum - 1)
  //       cout << G.vertices[topo[j]].data << " , ";
  //     else
  //       cout << G.vertices[topo[j]].data << endl;
  //   }
  // } else {
  //   cout << "网中存在环，无法进行拓扑排序！" << endl;
  // }

  if (!CriticalPath(G)) {
    cout << "网中存在环，无法进行拓扑排序！" << endl;
  }

  return 0;
}