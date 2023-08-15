#include "Polynomial.h"

string head_1, head_2;

//算法2.18 多项式的创建
void CreatPolyn(Polynomial &P, string filename) {
  Polynomial q, pre, s;
  P = new PNode;
  P->next = NULL;  //先建立一个带头结点的单链表
  fstream file;
  file.open(filename);
  if (!file) {
    cout << "error" << endl;
    exit(0);
  }
  file >> head_1 >> head_2;
  while (!file.eof()) {
    s = new PNode;
    file >> s->coef >> s->expn;
    pre = P;  // pre用于保存q的前驱，初值为头结点
    q = P->next;
    //通过比较指数找到第一个大于输入项指数的项q
    while (q && q->expn < s->expn) {
      pre = q;
      q = q->next;
    }
    s->next = q;  //将输入项s插入到q和其前驱结点pre之间
    pre->next = s;
  }
  file.close();
}

//算法2.19 多项式的相加
void AddPolyn(Polynomial &Pa, Polynomial &Pb) {
  //多项式加法：Pa=Pa+Pb，利用两个多项式的结点构成“和多项式”
  Polynomial r, p1, p2, p3;
  float sum = 0;
  p1 = Pa->next;
  p2 = Pb->next;  // p1和p2初值分别指向Pa和Pb的第一个结点
  p3 = Pa;        // p3指向和多项式的当前结点，初值为Pa
  while (p1 && p2) {
    if (p1->expn == p2->expn) {
      sum = p1->coef + p2->coef;
      if (sum) {
        p1->coef = sum;
        p3->next = p1;
        p3 = p1;
        p1 = p1->next;
        r = p2;
        p2 = p2->next;
        delete r;
      } else {
        r = p1;
        p1 = p1->next;
        delete r;
        r = p2;
        p2 = p2->next;
        delete r;
      }
    } else if (p1->expn < p2->expn) {
      p3->next = p1;
      p3 = p1;
      p1 = p1->next;
    } else {
      p3->next = p2;
      p3 = p2;
      p2 = p2->next;
    }
  }
  p3->next = p1 ? p1 : p2;
  delete Pb;
}

int main() {
  Polynomial Pa, Pb;
  Polynomial p;
  CreatPolyn(Pa, "PolyA.txt");
  CreatPolyn(Pb, "PolyB.txt");
  AddPolyn(Pa, Pb);
  p = Pa->next;
  int i = 0;
  while (p) {
    if (i) {
      cout << " + ";
    }
    cout << "(" << p->coef << ") * x^" << p->expn;
    p = p->next;
    i = 1;
  }
  cout << endl;
  return 0;
}