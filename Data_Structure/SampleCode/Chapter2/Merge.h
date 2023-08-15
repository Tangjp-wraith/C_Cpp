#pragma once

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/*------------算法2.15 线性表的合并（链表）------------*/

typedef struct LNode {
  int data;
  struct LNode *next;
} LNode, *List;

void InitList(List &L);

void ListInput(List &L, int n,string filename);

bool LocateElem(List L, int e);

void ListInsert(List &L, int e);

void ListOutput(List L);

void MergeList(List &LA, List LB);

/*------------算法2.16 顺序有序表的合并------------*/

#define MAXSIZE 100

typedef struct {
  int *elem;
  int length;
} SqList;

void InitList_Sq(SqList &L,int n);

void ListInput_Sq(SqList &L, int n,  string filename);

void ListOutput_Sq(SqList L);

void MergeList_Sq(SqList LA,SqList LB,SqList &LC);

/*------------算法2.17 链式有序表的合并------------*/

typedef struct LNode *LinkList;

void InitList_L(LinkList &L);

void ListInput_L(LinkList &L, int n,string filename);

void ListOutput_L(LinkList L);

void MergeList_L(LinkList &LA, LinkList &LB, LinkList &LC);