#include "Sort.h"

#include <iostream>
using namespace std;

//算法8.1 直接插入排序
void InsertSort(SqList &L) {
  int i, j;
  for (i = 2; i <= L.length; ++i) {
    if (L.r[i].key < L.r[i - 1].key) {  //"<"，需将r[i]插入有序子表
      L.r[0] = L.r[i];      //将待插入的记录暂存到监视哨中
      L.r[i] = L.r[i - 1];  // r[i-1]后移
      for (j = i - 2; L.r[0].key < L.r[j].key; --j) {  //从后向前寻找插入位置
        L.r[j + 1] = L.r[j];  //记录逐个后移，直到找到插入位置
      }
      L.r[j + 1] = L.r[0];  //将r[0]即原r[i]，插入到正确位置
    }
  }
}

//算法8.2 折半插入排序
void BInsertSort(SqList &L) {
  for (int i = 2; i <= L.length; ++i) {
    L.r[0] = L.r[i];  //将待插入的记录暂存到监视哨中
    int left = 0, right = i - 1;
    while (left <= right) {
      int mid = (left + right) / 2;  //在r[low..high]中折半查找插入的位置
      if (L.r[0].key < L.r[mid].key) {
        right = mid - 1;  //插入点在前一子表
      } else {
        left = mid + 1;  //插入点在后一子表
      }
      for (int j = i - 1; j >= right + 1; --j) {
        L.r[j + 1] = L.r[j];  //记录后移
      }
      L.r[right + 1] = L.r[0];  //将r[0]即原r[i]，插入到正确位置
    }
  }
}

void Create_Sq(SqList &L) {
  int n = rand() % MAXSIZE + 5;
  for (int i = 1; i <= n; i++) {
    L.r[i].key = rand() % 100;
    L.length++;
  }
}

void Show_Sq(SqList L) {
  int i;
  for (i = 1; i <= L.length; i++) {
    cout << L.r[i].key << " ";
  }
  cout << endl;
}

int main() {
  SqList L;
  L.r = new ElemType[MAXSIZE + 10];
  L.length = 0;
  Create_Sq(L);

  // cout << "Before InsertSort: " << endl;
  // Show_Sq(L);
  // InsertSort(L);
  // cout << "After InsertSort: " << endl;
  // Show_Sq(L);

  cout << "Before BInsertSort: " << endl;
  Show_Sq(L);
  BInsertSort(L);
  cout << "After BInsertSort: " << endl;
  Show_Sq(L);

  return 0;
}