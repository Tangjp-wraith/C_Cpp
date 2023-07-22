#include "Merge.h"

#include <cstddef>

/*------------算法2.15 线性表的合并（链表）------------*/

void InitList(List &L) {
  L = new LNode;
  L->next = NULL;
}

void ListInput(List &L, int n, string filename) {
  List p, r;
  r = L;
  fstream file;
  file.open(filename);
  if (!file) {
    cout << "error!" << endl;
    exit(0);
  }
  while (!file.eof()) {
    p = new LNode;
    file >> p->data;
    p->next = NULL;
    r->next = p;
    r = p;
    n++;
  }
  file.close();
}

bool LocateElem(List L, int e) {
  List p;
  p = L->next;
  while (p != NULL) {
    if (p->data == e) {
      return true;
    }
    p = p->next;
  }
  return false;
}

void ListInsert(List &L, int e) {
  List p;
  p = new LNode;
  p->data = e;
  p->next = L->next;
  L->next = p;
}

void ListOutput(List L) {
  List p;
  p = L->next;
  while (p != NULL) {
    cout << p->data << " ";
    p = p->next;
  }
  cout << endl;
}

//算法2.15 线性表的合并（链表）
void MergeList(List &LA, List LB) {
  List p = LB->next;
  while (p != NULL) {
    int e = p->data;
    if (!LocateElem(LA, e)) {
      ListInsert(LA, e);
    }
    p = p->next;
  }
}

/*------------算法2.16 顺序有序表的合并------------*/

void InitList_Sq(SqList &L, int n) {
  L.elem = new int[MAXSIZE];
  if (!L.elem) {
    exit(0);
  }
  L.length = 0;
}

void ListInput_Sq(SqList &L, int n, string filename) {
  fstream file;
  file.open(filename);
  if (!file) {
    cout << "error!" << endl;
    exit(0);
  }
  int i = 0;
  while (!file.eof()) {
    file >> L.elem[i];
    ++i;
  }
  L.length = i;
}

void ListOutput_Sq(SqList L) {
  for (int i = 0; i < L.length; ++i) {
    cout << L.elem[i] << " ";
  }
  cout << endl;
}

void MergeList_Sq(SqList LA, SqList LB, SqList &LC) {
  //已知顺序有序表LA和LB的元素按值非递减排列
  //归并LA和LB得到新的顺序有序表LC，LC的元素也按值非递减排列
  int *pa, *pb, *pc, *pa_last, *pb_last;
  pa = LA.elem;
  pb = LB.elem;
  LC.length = LA.length + LB.length;
  LC.elem = new int[LC.length];
  pc = LC.elem;
  pa_last = LA.elem + LA.length - 1;
  pb_last = LB.elem + LB.length - 1;
  while (pa <= pa_last && pb <= pb_last) {
    if (*pa <= *pb) {
      *pc++ = *pa++;
    } else {
      *pc++ = *pb++;
    }
  }
  while (pa <= pa_last) {
    *pc++ = *pa++;
  }
  while (pb <= pb_last) {
    *pc++ = *pb++;
  }
}

/*------------算法2.17 链式有序表的合并------------*/

typedef struct LNode *LinkList;

void InitList_L(LinkList &L) { InitList(L); }

void ListInput_L(LinkList &L, int n, string filename) {
  ListInput(L, n, filename);
}

void ListOutput_L(LinkList L) { ListOutput(L); }

void MergeList_L(LinkList &LA, LinkList &LB, LinkList &LC) {
  //已知单链表LA和LB的元素按值非递减排列
  //归并LA和LB得到新的单链表LC，LC的元素也按值非递减排列
  LinkList pa, pb, pc;
  pa = LA->next;
  pb = LB->next;
  LC = LA;
  pc = LC;
  while (pa && pb) {
    if (pa->data <= pb->data) {
      pc->next = pa;
      pc = pa;
      pa = pa->next;
    } else {
      pc->next = pb;
      pc = pb;
      pb = pb->next;
    }
  }
  pc->next = pa ? pa : pb;
  delete LB;
}

int main() {
  /*------------算法2.15 线性表的合并（链表）------------*/
  // int n = 0, m = 0;
  // List LA, LB;
  // InitList(LA);
  // InitList(LB);
  // ListInput(LA, n, "ListA.txt");
  // ListInput(LB, m, "ListB.txt");
  // MergeList(LA, LB);
  // ListOutput(LA);

  /*------------算法2.16 顺序有序表的合并------------*/
  // SqList LA, LB, LC;
  // int num_a = 0, num_b = 0, num_c = 0;
  // InitList_Sq(LA, num_a);
  // InitList_Sq(LB, num_b);
  // InitList_Sq(LC, num_c);
  // ListInput_Sq(LA, num_a, "ListA.txt");
  // ListInput_Sq(LB, num_b, "ListB.txt");
  // MergeList_Sq(LA, LB, LC);
  // ListOutput_Sq(LC);

  /*------------算法2.17 链式有序表的合并------------*/
  LinkList LA, LB, LC;
  int num_a = 0, num_b = 0, num_c = 0;
  InitList_L(LA);
  InitList_L(LB);
  InitList_L(LC);
  ListInput_L(LA, num_a, "ListA.txt");
  ListInput_L(LB, num_b, "ListB.txt");
  MergeList_L(LA, LB, LC);
  ListOutput_L(LC);
}