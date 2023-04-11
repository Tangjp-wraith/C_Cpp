#include "BiThrTree.h"

#include <iostream>

using namespace std;

//全局变量pre
BiThrNode *pre = new BiThrNode;

void CreateBiTree(BiThrTree &T) {
  char ch;
  cin >> ch;
  if (ch == '#') T = NULL;  
  else {
    T = new BiThrNode;
    T->data = ch;          
    CreateBiTree(T->lchild);  
    CreateBiTree(T->rchild); 
  }                        
}  

//算法5.7 以节点p为根的子树中序线索化
void InThreading(BiThrTree p) {

}
