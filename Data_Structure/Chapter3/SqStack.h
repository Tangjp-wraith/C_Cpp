#include <fstream>
#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100  //顺序栈存储空间的初始分配量
typedef int Status;
typedef char SElemType;

typedef struct {
  SElemType *base;  //栈底指针
  SElemType *top;   //栈顶指针
  int stacksize;    //栈可用的最大容量
} SqStack;

//算法3.1　顺序栈的初始化
Status InitStack(SqStack &S);

//算法3.2　顺序栈的入栈
Status Push(SqStack &S, SElemType e);

//算法3.3　顺序栈的出栈
Status Pop(SqStack &S, SElemType &e);

//算法3.4　取顺序栈的栈顶元素
char GetTop(SqStack S);