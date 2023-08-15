#pragma once

#include <iostream>
using namespace std;
#define FALSE 0
#define TRUE 1
#define OK 1
#define m 3  // B-树的阶，暂设为3

typedef struct BTNode {
  int keynum;          //结点中关键字的个数，即结点的大小
  BTNode *parent;      //指向双亲结点
  int key[m + 1];      //关键字矢量，0号单元未用
  BTNode *ptr[m + 1];  //子树指针矢量
} BTNode, *BTree;

// B-树的查找结果类型定义
struct Result {
  BTNode *pt;  //指向找到的结点
  int i;       // 1..m，在结点中的关键字序号
  int tag;     // 1：查找成功，0：查找失败
};

int Search(BTree T, int key);
void Insert(BTree &q, int i, int x, BTree &ap);
void split(BTree &q, int s, BTree &ap);
void NewRoot(BTree &T, BTree q, int x, BTree &ap);
void InitialBTree(BTree &T);
//算法7.8　B-树的查找
Result SearchBTree(BTree &T, int key);
//算法7.9　B-树的插入
int InsertBTree(BTree &T, int K, BTree q, int i);