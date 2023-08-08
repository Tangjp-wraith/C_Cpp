#pragma once

#include <iostream>

// 开放地址法哈希表的存储表示
#define m 16

struct HashTable {
  int key;  //关键字项
};

//算法7.10为哈希表查找的算法，采用线性探测法处理冲突
int H(int key) ;
int SearchHash(HashTable HT[], int key);
