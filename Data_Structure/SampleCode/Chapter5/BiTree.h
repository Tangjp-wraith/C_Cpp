#pragma once

typedef struct BiNode {  //二叉链表定义
  char data;
  struct BiNode *lchild, *rchild;
} BiTNode, *BiTree;

//算法5.1 中序遍历的递归算法
void InOrderTraverse(BiTree T);

//算法5.2 中序遍历的非递归算法
void InOrderTraverse1(BiTree T);

//算法5.3 先序遍历的顺序建立二叉链表
void CreateBiTree(BiTree &T);

//算法5.4 复制二叉树
void Copy(BiTree T,BiTree &NewT);

//算法5.5 计算二叉树的深度
int Depth(BiTree T);

//算法5.6 统计二叉树中的节点
int NodeCount(BiTree T);

//统计叶节点（度为0）的个数
int LeafNode(BiTree T);

//后序遍历的非递归算法
void PostOrder(BiTree T);