#include "SSTable.h"

using std::cout;
using std::endl;

int InitList_SSTable(SSTable &L) {
  L.R = new ElemType[MAXSIZE];
  if (!L.R) {
    cout << "error" << endl;
    return 0;
  }
  L.length = 0;
  return OK;
}

int Insert_SSTable(SSTable &L) {
  int j = 0;
  for (int i = 0; i < MAXSIZE; ++i) {
    L.R[i].key = j;
    L.length++;
    ++j;
  }

  return OK;
}

//算法7.1　顺序查找
int Search_Seq(SSTable ST, int key) {
  //在顺序表ST中顺序查找其关键字等于key的数据元素。若找到，则函数值为
  //该元素在表中的位置，否则为0
  for (int i = ST.length; i >= 1; --i) {
    if (ST.R[i].key == key) {
      return i;
    }
  }
  return 0;
}
//算法7.2　设置监视哨的顺序查找
int Search_Seq_U(SSTable ST, int key) {
  ST.R[0].key = key;
  int i;
  for (i = ST.length; ST.R[i].key != key; --i)
    ;
  return i;
}

//算法7.3　折半查找
int Search_Bin(SSTable ST, int key) {
  int low = 1, high = ST.length;
  while (low <= high) {
    int mid = (low + high) / 2;
    if (key == ST.R[mid].key) {
      return mid;
    } else if (key < ST.R[mid].key) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return 0;
}

void Show_End(int result, int testkey) {
  if (result == 0)
    cout << "未找到" << testkey << endl;
  else
    cout << "找到" << testkey << "位置为" << result << endl;
  return;
}

int main() {
  SSTable ST;
  InitList_SSTable(ST);
  Insert_SSTable(ST);
  int testkey1 = rand() % 100, testkey2 = rand() % 100;
  int result;
  result = Search_Bin(ST, testkey1);
  Show_End(result, testkey1);
  result = Search_Bin(ST, testkey2);
  Show_End(result, testkey2);
}