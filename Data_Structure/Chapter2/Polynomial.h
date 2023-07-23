#pragma once

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

typedef struct PNode {
  float coef;  // 系数
  int expn;    //指数
  struct PNode *next;
} PNode, *Polynomial;

//算法2.18 多项式的创建
void CreatPolyn(Polynomial &P, string filename) ;

//算法2.19 多项式的相加
void AddPolyn(Polynomial &Pa, Polynomial &Pb);
