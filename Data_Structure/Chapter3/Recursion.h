#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef char ElemType;

typedef struct LNode {
  ElemType data;     //结点的数据域
  LNode *next;       //结点的指针域
} LNode, *LinkList;  //头指针

//后插法创建链表算法
void CreateList_L(LinkList &L, int n);

//算法3.9　遍历输出链表中各个结点的递归算法
void TraverseList(LinkList p);

//算法3.10　Hanoi塔问题的递归算法
void move(char A, int n, char C);
void Hanoi(int n, char A, char B, char C);