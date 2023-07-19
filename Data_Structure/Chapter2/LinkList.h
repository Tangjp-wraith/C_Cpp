#pragma once

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;  // Status 是函数返回值类型，其值是函数结果状态代码。
typedef int ElemType;  // ElemType 为可定义的数据类型，此设为int类型

struct Book {
  string id;     // ISBN
  string name;   //书名
  double price;  //定价
};

typedef struct LNode {
  Book data;           //结点的数据域
  struct LNode *next;  //结点的指针域
} LNode, *LinkList;    // LinkList为指向结构体LNode的指针类型

//算法2.6 单链表的初始化
Status InitList_L(LinkList &L);

//算法2.7 单链表的取值
Status GetElem_L(LinkList L, int i, Book &e);

//算法2.8 按值查找
LNode *LocateElem_L(LinkList L, int e);

//算法2.9 单链表的插入
Status ListInsert_L(LinkList &L, int i, Book &e);

//算法2.10 单链表的删除
Status ListDelete_L(LinkList &L, int i);

//算法2.11 前插法创建单链表
void CreateList_H(LinkList &L, int n);

//算法2.12 后插法创建单链表
void CreateList_R(LinkList &L, int n);
 