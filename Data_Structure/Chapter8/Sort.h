#pragma once

#define MAXSIZE 10

typedef struct {
  int key;
  char *otherinfo;
} ElemType;
//顺序表的存储结构
typedef struct {
  ElemType *r;  //存储空间的基地址
  int length;   //顺序表长度
} SqList;

//算法8.1 直接插入排序
void InsertSort(SqList &L);

//算法8.2 折半插入排序
void BInsertSort(SqList &L);

//算法8.3 希尔排序