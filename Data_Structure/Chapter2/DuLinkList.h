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

typedef struct DuLNode {
  Book data;              //数据域
  struct DuLNode *prior;  //直接前驱
  struct DuLNode *next;   //直接后继
} DuLNode, *DuLinkList;

// 双向链表的初始化
Status InitDuList_L(DuLinkList &L);

// 双向链表的取值
DuLNode *GetElemP_DuL(DuLinkList L, int i);

//算法2.13 双向链表的插入
Status ListInsert_DuL(DuLinkList &L, int i, Book e);

//算法2.14 双向链表的删除
Status ListDelete_DuL(DuLinkList &L, int i);

//创建双向链表
void CreateDuList_L(DuLinkList &L);
