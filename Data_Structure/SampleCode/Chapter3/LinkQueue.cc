#include "LinkQueue.h"

//算法3.16　链队的初始化
Status InitQueue(LinkQueue &Q) {
  Q.front = Q.rear = new QNode;
  Q.front->next = NULL;
  return OK;
}

//算法3.17　链队的入队
Status EnQueue(LinkQueue &Q, QElemType e) {
  QueuePtr p;
  p = new QNode;
  p->data = e;
  p->next = NULL;
  Q.rear->next = p;
  Q.rear = p;
  return OK;
}

//算法3.18　链队的出队
Status DeQueue(LinkQueue &Q, QElemType &e) {
  QueuePtr p;
  if (Q.front == Q.rear) {
    return ERROR;
  }
  p = Q.front->next;
  e = p->data;
  Q.front->next = p->next;
  if (Q.rear == p) {
    Q.rear = Q.front;
  }
  delete p;
  return OK;
}

//算法3.19　取链队的队头元素
SElemType GetHead(LinkQueue Q) {
  if (Q.front != Q.rear) {
    return Q.front->next->data;
  }
  return 0;
}

int main() {
  int choose, flag = 0;
  LinkQueue Q;
  QElemType e, j;
  cout << "1.初始化\n";
  cout << "2.入队\n";
  cout << "3.读队头元素\n";
  cout << "4.出队\n";
  cout << "0.退出\n\n";

  choose = -1;
  while (choose != 0) {
    cout << "请选择:";
    cin >> choose;
    switch (choose) {
      case 1:  //算法3.16　链队的初始化
        if (InitQueue(Q)) {
          flag = 1;
          cout << "成功对队列进行初始化\n\n";
        } else
          cout << "初始化队列失败\n\n";
        break;
      case 2: {  //算法3.17　链队的入队
        fstream file;
        file.open("QNode.txt");
        if (!file) {
          cout << "错误！未找到文件！\n\n" << endl;
          exit(ERROR);
        }
        if (flag) {
          flag = 1;
          cout << "入队的元素依次为：\n";
          while (!file.eof()) {
            file >> j;
            if (file.fail())
              break;
            else {
              EnQueue(Q, j);
              cout << j << "  ";
            }
          }
          cout << endl << endl;
        } else
          cout << "队列未建立，请重新选择\n\n";
        file.close();
      } break;
      case 3:  //算法3.19　取链队的队头元素
        if (flag != -1 && flag != 0)
          cout << "队头元素为：\n" << GetHead(Q) << endl << endl;
        else
          cout << "队列中无元素，请重新选择\n" << endl;
        break;
      case 4:  //算法3.18　链队的出队
        cout << "依次弹出的队头元素为:\n";
        while (DeQueue(Q, e)) {
          flag = -1;
          cout << e << "  ";
        }
        cout << endl << endl;
        break;
    }
  }
  return 0;
}