#pragma once

#include <iostream>

#define MAXSIZE 100
#define OK 1;

typedef struct {
  int key;
} ElemType;

typedef struct {
  ElemType *R;
  int length;
} SSTable;

int InitList_SSTable(SSTable &L);
int Insert_SSTable(SSTable &L);
//算法7.1　顺序查找
int Search_Seq(SSTable ST, int key);
void Show_End(int result, int testkey);

//算法7.2　设置监视哨的顺序查找
int Search_Seq_U(SSTable ST, int key);

//算法7.3　折半查找
int Search_Bin(SSTable ST, int key);