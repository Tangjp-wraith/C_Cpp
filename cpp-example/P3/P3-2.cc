#include <iostream>

using namespace std;

struct X {
  void f() { std::cout << "6\n"; }
  void f(int) { std::cout << "int\n"; }
};

void f2(void (X::*p)(), X* x, int n) { (x->*p)(); }

void f3(void (X::*p)(int), X* x, int n) { (x->*p)(n); }

int main() {
  X x;
  f2(&X::f, &x, 5);  // 6
  f3(&X::f, &x, 5); // int
}