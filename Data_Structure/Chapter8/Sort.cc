#include "Sort.h"

#include <iostream>
using namespace std;

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

//算法8.3 希尔排序
void ShellInsert(SqList &L, int dk) {
  int i, j;  //对顺序表L做一趟增量是dk的希尔插入排序
  for (i = dk + 1; i <= L.length; ++i) {
    if (L.r[i].key < L.r[i - dk].key) {  //需将L.r[i]插入有序增量子表
      L.r[0] = L.r[i];                   //暂存在L.r[0]
      for (j = i - dk; j > 0 && L.r[0].key < L.r[j].key; j -= dk) {
        L.r[j + dk] = L.r[j];  //记录后移，直到找到插入位置
      }
      L.r[j + dk] = L.r[0];  //将r[0]即原r[i]，插入到正确位置
    }
  }
}
void ShellSort(SqList &L, int dt[], int t) {
  for (int k = 0; k < t; ++k) {  //按增量序列dt[0..t-1]对顺序表L作t趟希尔排序
    ShellInsert(L, dt[k]);  //一趟增量为dt[t]的希尔插入排序
    cout << k + 1 << " ShellInsert: " << endl;
    Show_Sq(L);
  }
}

//算法8.4 冒泡排序
void BubbleSort(SqList &L) {
  bool flag = true;  // flag用来标记某一趟排序是否发生交换
  int end = L.length - 1;
  while (end > 0 && flag) {
    flag = false;  // flag置为0，如果本趟排序没有发生交换，则不会执行下一趟排序
    for (int j = 1; j <= end; ++j) {
      if (L.r[j].key > L.r[j + 1].key) {
        flag = true;         // flag置为1，表示本趟排序发生了交换
        auto temp = L.r[j];  //交换前后两个记录
        L.r[j] = L.r[j + 1];
        L.r[j + 1] = temp;
      }
    }
    --end;
  }
}

//算法8.5 快速排序
int Partition(SqList &L, int low, int high) {
  //对顺序表L中的子表r[low..high]进行一趟排序，返回枢轴位置
  int pivotkey;
  L.r[0] = L.r[low];        //用子表的第一个记录做枢轴记录
  pivotkey = L.r[low].key;  //枢轴记录关键字保存在pivotkey中
  while (low < high) {      //从表的两端交替地向中间扫描
    while (low < high && L.r[high].key >= pivotkey) {
      --high;
    }
    L.r[low] = L.r[high];  //将比枢轴记录小的记录移到低端
    while (low < high && L.r[low].key <= pivotkey) {
      ++low;
    }
    L.r[high] = L.r[low];  //将比枢轴记录大的记录移到高端
  }
  L.r[low] = L.r[0];  //枢轴记录到位
  return low;         //返回枢轴位置
}
void QSort(SqList &L, int low, int high) {
  int pivotkey;  //对顺序表L中的子序列L.r[low..high]做快速排序
  if (low < high) {
    //将L.r[low..high]一分为二，pivotloc是枢轴位置
    pivotkey = Partition(L, low, high);
    QSort(L, low, pivotkey - 1);   //对左子表递归排序
    QSort(L, pivotkey + 1, high);  //对右子表递归排序
  }
}
void QuickSort(SqList &L) { QSort(L, 1, L.length); }

//算法8.6 简单选择排序
void SelectSort(SqList &L) {
  //在L.r[i..L.length] 中选择关键字最小的记录
  for (int i = 1; i < L.length; ++i) {
    int k = i;
    for (int j = i + 1; j <= L.length; ++j) {
      if (L.r[j].key < L.r[k].key) {
        k = j;  // k指向此趟排序中关键字最小的记录
      }
    }
    if (k != i) {
      auto temp = L.r[i];
      L.r[i] = L.r[k];
      L.r[k] = temp;
    }
  }
}

//算法8.7 筛选法调整堆
void HeapAdjust(SqList &L, int s, int m) {
  auto rc = L.r[s];
  //假设r[s+1..m]已经是堆，将r[s..m]调整为以r[s]为根的大根堆
  for (int j = 2 * s; j <= m; j *= 2) {  //沿key较大的孩子结点向下筛选
    if (j < m && L.r[j].key < L.r[j + 1].key) ++j;  // j为key较大的记录的下标
    if (rc.key >= L.r[j].key) break;                // rc应插入在位置s上
    L.r[s] = L.r[j];
    s = j;
  }
  L.r[s] = rc;
}

//算法8.8 建初堆
void CreatHeap(SqList &L) {
  //把无序序列L.r[1..L.length]建成大根堆
  for (int i = L.length / 2; i > 0; --i) {
    HeapAdjust(L, i, L.length);
  }
}

//算法8.9 堆排序
void HeapSort(SqList &L) {
  CreatHeap(L);  //把无序序列L.r[1..L.length]建成大根堆
  for (int i = L.length; i > 1; --i) {
    //将堆顶记录和当前未经排序子序列L.r[1..i]中最后一个记录互换
    auto x = L.r[1];
    L.r[1] = L.r[i];
    L.r[i] = x;
    HeapAdjust(L, 1, i - 1);  //将L.r[1..i-1]重新调整为大根堆
  }
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

  // cout << "Before BInsertSort: " << endl;
  // Show_Sq(L);
  // BInsertSort(L);
  // cout << "After BInsertSort: " << endl;
  // Show_Sq(L);

  // cout << "Before ShellSort: " << endl;
  // Show_Sq(L);
  // int *dt = new int[5];
  // int t = 3;
  // dt[0] = 5, dt[1] = 3, dt[2] = 1;
  // ShellSort(L, dt, t);
  // cout << "After ShellSort: " << endl;
  // Show_Sq(L);

  // cout << "Before QuickSort: " << endl;
  // Show_Sq(L);
  // QuickSort(L);
  // cout << "After QuickSort: " << endl;
  // Show_Sq(L);

  // cout << "Before SelectSort: " << endl;
  // Show_Sq(L);
  // SelectSort(L);
  // cout << "After SelectSort: " << endl;
  // Show_Sq(L);

  cout << "Before HeapSort: " << endl;
  Show_Sq(L);
  HeapSort(L);
  cout << "After HeapSort: " << endl;
  Show_Sq(L);

  return 0;
}