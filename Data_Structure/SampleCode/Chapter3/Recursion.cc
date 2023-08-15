#include "Recursion.h"

//后插法创建链表算法
void CreateList_L(LinkList &L, int n) {
  L = new LNode;
  L->next = NULL;
  LNode *p, *r;
  r = L;
  for (int i = 0; i < n; ++i) {
    p = new LNode;
    cin >> p->data;
    p->next = NULL;
    r->next = p;
    r = p;
  }
}

//算法3.9　遍历输出链表中各个结点的递归算法
void TraverseList(LinkList p) {
  if (p == NULL) {
    return;
  } else {
    cout << p->data << endl;
    TraverseList(p->next);  // p指向后继指点继续递归
  }
}

int m = 0;

//算法3.10　Hanoi塔问题的递归算法
void move(char A, int n, char C) {
  cout << "第" << ++m << "步,"
       << "将编号为" << n << "的圆盘从第" << A << "个柱子上移到第" << C
       << "个柱子上" << endl;
}
void Hanoi(int n, char A, char B, char C) {
  if (n == 1) {
    move(A, 1, C);
  }  //将编号为1的圆盘从A移到C
  else {
    Hanoi(n - 1, A, C, B);  //将A上编号为1至n-1的圆盘移到B，C做辅助塔
    move(A, n, C);          //将编号为n的圆盘从A移到C
    Hanoi(n - 1, B, A, C);  //将B上编号为1至n-1的圆盘移到C，A做辅助塔
  }
}

int main() {

  // int n;
  // LinkList L;
  // cout << "请输入元素个数：" << endl;
  // cin >> n;
  // cout << "请输入链表元素(以空格隔开，按回车结束)：" << endl;
  // CreateList_L(L, n);  //后插法创建链表算法
  // cout << "链表中的元素依次为：" << endl;
  // TraverseList(L->next);
  // cout << endl;
  // return 0;
  
  int n;
  char a, b, c;
  a = '1';
  b = '2';
  c = '3';
  cout << "请输入初始第一个柱子上的圆盘个数：" << endl;
  cin >> n;
  cout << "将第一个柱子上的圆盘全部移动到第三个柱子上的过程为：" << endl;
  Hanoi(n, a, b, c);
  return 0;
}