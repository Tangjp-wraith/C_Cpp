#pragma once

#include <cstring>
#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
#define MAXSTRLEN 255                 //用户可在255以内定义最长串长
typedef char SString[MAXSTRLEN + 1];  // 0号单元存放串的长度

Status StrAssign(SString T, string chars);

//算法4.1　BF算法
int Index(SString S, SString T, int pos);

//算法4.2　KMP算法
int Index_KMP(SString S, SString T, int pos, int next[]);

//算法4.3　计算next函数值
void get_next(SString T, int next[]);

//算法4.4　计算next函数修正值
void get_nextval(SString T, int nextval[]);

typedef struct {
  char ch[600];
  int len;
} HString;

//算法4.5　计算next函数修正值
void Virus_detection();