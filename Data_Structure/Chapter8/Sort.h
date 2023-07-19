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

void Create_Sq(SqList &L);
void Show_Sq(SqList L);
void Create_Elem(ElemType *R);

//算法8.1 直接插入排序
void InsertSort(SqList &L);

//算法8.2 折半插入排序
void BInsertSort(SqList &L);

//算法8.3 希尔排序
void ShellInsert(SqList &L, int dk);
void ShellSort(SqList &L, int dt[], int t);

//算法8.4 冒泡排序
void BubbleSort(SqList &L);

//算法8.5 快速排序
int Partition(SqList &L, int low, int high);
void QSort(SqList &L, int low, int high);
void QuickSort(SqList &L);

//算法8.6 简单选择排序
void SelectSort(SqList &L);

//算法8.7 筛选法调整堆
void HeapAdjust(SqList &L, int s, int m);
//算法8.8 建初堆
void CreatHeap(SqList &L);
//算法8.9 堆排序
void HeapSort(SqList &L);

//算法8.10 相邻两个有序子序列的归并
void Merge(ElemType R[], ElemType T[], int low, int mid, int high);
void Show_Merged(ElemType *T, int low, int high);

//算法8.11 归并排序
void MSort(ElemType R[], ElemType T[], int low, int high);
void MergeSort(SqList &L);

//算法8.12 基数排序