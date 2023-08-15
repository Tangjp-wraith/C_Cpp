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

struct Book{
  string id;
  string name;
  double price;
};

typedef struct {
  Book *elem;
  int length;
}SqList;

//算法2.1 顺序表的初始化
Status InitList_Sq(SqList &L);

//算法2.2　顺序表的取值
Status GetElem(SqList L, int i, Book &e);

//算法2.3 顺序表的查找
int LocateElem_Sq(SqList L, double e);

//算法2.4 顺序表的插入
Status ListInsert_Sq(SqList &L, int i, Book e);

//算法2.5 顺序表的删除
Status ListDelete_Sq(SqList &L, int i);