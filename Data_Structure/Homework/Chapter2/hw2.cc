#include <cstddef>
#include <iostream>

using namespace std;

typedef struct LNode {
  int data;
  struct LNode *next;
} LNode, *LinkList;

void Merge(LinkList &a, LinkList &b) {
  LinkList pa = a->next, pb = b->next;
  LinkList pc = a;
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
  delete b;
}

int main() {
  LinkList a = new LNode;
  a->next = NULL;
  LinkList b = new LNode;
  b->next = NULL;
  LinkList p, pa = a, pb = b;
  for (int i = 1; i < 20; i += 2) {
    p = new LNode;
    p->data = i;
    p->next = NULL;
    pa->next = p;
    pa = p;
  }
  for (int i = 1; i < 10; i += 2) {
    p = new LNode;
    p->data = i;
    p->next = NULL;
    pb->next = p;
    pb = p;
  }
  Merge(a, b);
  a = a->next;
  while (a) {
    cout << a->data << " ";
    a = a->next;
  }
  cout << endl;
  return 0;
}