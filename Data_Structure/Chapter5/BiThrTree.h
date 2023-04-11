#pragma once

typedef struct BiThrNode {
  char data;
  struct BiThrNode *lchild, *rchild;
  int LTag, RTag;
} BiThrNode, *BiThrTree;

//算法5.7 以节点p为根的子树中序线索化
void InThreading(BiThrTree p);

