#include "BiTree.h"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <stack>

using namespace std;

//算法5.1 中序遍历的递归算法
void InOrderTraverse(BiTree T) {
  if (T) {
    InOrderTraverse(T->lchild);
    cout << T->data << " ";
    InOrderTraverse(T->rchild);
  }
}

//算法5.2 中序遍历的非递归算法
void InOrderTraverse1(BiTree T) {
  BiTree p;
  stack<BiTree> S;
  BiTree q = new BiTNode;
  p = T;
  while (p || !S.empty()) {
    if (p) {
      S.push(p);  // p非空根指针进栈，遍历左子树
      p = p->lchild;
    } else {
      q = S.top();
      S.pop();  // p为空根指针退栈，访问根结点，遍历右子树
      cout << q->data << " ";
      p = q->rchild;
    }
  }
}

//算法5.3 先序遍历的顺序建立二叉链表
void CreateBiTree(BiTree &T) {
  //按先序次序输入二叉树中结点的值（一个字符），创建二叉链表表示的二叉树T
  char ch;
  cin >> ch;
  if (ch == '#') {  //递归结束，建空树
    T = NULL;
  } else {
    T = new BiTNode;
    T->data = ch;             //生成根结点
    CreateBiTree(T->lchild);  //递归创建左子树
    CreateBiTree(T->rchild);  //递归创建右子树
  }
}

//算法5.4 复制二叉树
void Copy(BiTree T, BiTree &NewT) {
  if (T == NULL) {
    NewT = NULL;
    return;
  }
  NewT = new BiTNode;
  NewT->data = T->data;
  Copy(T->lchild, NewT->lchild);
  Copy(T->rchild, NewT->rchild);
}

//算法5.5 计算二叉树的深度
int Depth(BiTree T) {
  if (T == NULL) {
    return 0;
  }
  int m, n;
  m = Depth(T->lchild);
  n = Depth(T->rchild);
  if (m > n) return m + 1;  // 二叉树的深度为m和n中较大者+1
  return n + 1;
}

//算法5.6 统计二叉树中的节点
int NodeCount(BiTree T) {
  
}

int main() {
  BiTree tree;  // ABC##DE#G##F###
  CreateBiTree(tree);
  // InOrderTraverse(tree);
  InOrderTraverse1(tree);
  cout << endl;

  BiTree New;
  Copy(tree, New);
  InOrderTraverse(New);
  cout << endl;

  cout << Depth(tree) << endl;
}