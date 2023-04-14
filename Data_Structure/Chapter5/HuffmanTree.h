#pragma once

typedef struct {
  int weight;
  int parent, lchild, rchild;
} HTNode, *HuffmanTree;

void Select(HuffmanTree HT, int len, int &s1, int &s2);

//算法5.10 构造哈夫曼树
void CreatHuffmanTree(HuffmanTree &HT, int n);