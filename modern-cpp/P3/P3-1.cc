#include <iostream>

using namespace std;

// 成员函数指针
// 成员函数指针则真的存储了一个地址

struct X {
  void f() { std::cout << "6" << std::endl; }
};
// 引用
void f2(void (X::*p)(), X& x) { (x.*p)(); }
// 指针
void f3(void (X::*p)(), X* x) { (x->*p)(); }

int main() {
  void (X::*p)() = &X::f;
  X x;
  (x.*p)();  // 6
  X x1;
  f2(&X::f, x1);
  X x2;
  f3(&X::f, &x2);
}