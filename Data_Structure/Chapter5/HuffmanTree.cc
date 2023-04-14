#include "HuffmanTree.h"

#include <iostream>

using namespace std;

void Select(HuffmanTree HT, int len, int &s1, int &s2) {
  int minx1 = 0x3f3f3f3f, minx2 = 0x3f3f3f3f;
  for (int i = 1; i < len; ++i) {
    if (HT[i].weight < minx1 && HT[i].parent == 0) {
      minx1 = HT[i].weight;
      s1 = i;
    }
  }
  int temp = HT[s1].weight;
  HT[s1].weight = 0x3f3f3f3f;
  for (int i = 1; i < len; ++i) {
    if (HT[i].weight < minx2 && HT[i].parent == 0) {
      minx2 = HT[i].weight;
      s2 = i;
    }
  }
  HT[s1].weight = temp;
}

//算法5.10 构造哈夫曼树
void CreatHuffmanTree(HuffmanTree &HT, int n) {
  int s1, s2;
  if (n <= 1) {
    return;
  }
  int m = 2 * n - 1;
  HT = new HTNode[m + 1];
  for (int i = 1; i <= m; ++i) {
    HT[i].parent = HT[i].lchild = HT[i].rchild = 0;
  }
  cout << "输入叶子节点的权值:\n";
  for (int i = 1; i <= n; ++i) {
    cin >> HT[i].weight;
  }
  //通过n-1次的选择、删除、合并来创建赫夫曼树
  for (int i = n + 1; i <= m; ++i) {
    //在HT[k](1≤k≤i-1)中选择两个其双亲域为0且权值最小的结点,
    // 并返回它们在HT中的序号s1和s2
    Select(HT, i - 1, s1, s2);
    HT[s1].parent = i;
    HT[s2].parent = i;
    //得到新结点i，从森林中删除s1，s2，将s1和s2的双亲域由0改为i
    HT[i].lchild = s1;
    HT[i].rchild = s2;  // s1,s2分别作为i的左右孩子
    HT[i].weight = HT[s1].weight + HT[s2].weight;  // i 的权值为左右孩子权值之和
  }
}

