#pragma once

typedef struct BiThrNode {
  char data;
  struct BiThrNode *lchild, *rchild;
  int LTag, RTag;
} BiThrNode, *BiThrTree;

// 先序遍历建二叉链表
void CreateBiTree(BiThrTree &T);

//算法5.7 以节点p为根的子树中序线索化
void InThreading(BiThrTree p);

//算法5.8 带头节点的二叉树中序线索化
void InOrderThreading(BiThrTree &Thrt, BiThrTree T);

//算法5.9 遍历中序线索二叉树
void InOrderTraverse_Thr(BiThrTree T);