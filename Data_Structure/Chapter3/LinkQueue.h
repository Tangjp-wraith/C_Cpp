#include <fstream>
#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int QElemType;
typedef int Status;
typedef int SElemType;

/*--------队列的链式存储结构--------*/
typedef struct QNode {
  QElemType data;
  struct QNode *next;
} QNode, *QueuePtr;

typedef struct {
  QueuePtr front;
  QueuePtr rear;
} LinkQueue;

//算法3.16　链队的初始化
Status InitQueue(LinkQueue &Q);

//算法3.17　链队的入队
Status EnQueue(LinkQueue &Q, QElemType e);

//算法3.18　链队的出队
Status DeQueue(LinkQueue &Q, QElemType &e);

//算法3.19　取链队的队头元素
SElemType GetHead(LinkQueue Q);