#include <iostream>

using namespace std;

// 证明普通的成员函数指针是存了明确的地址的
// wraning 但可执行

struct X {
  void f() { std::cout << "func\n"; }
};
int main() {
  using Func = void (*)(X* const);
  auto p = &X::f;
  auto func = (Func)(p);
  func(nullptr);  //打印func
}