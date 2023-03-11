#include <iostream> 

using namespace std;

// 数据成员指针

struct X {
  int x = 1;
};

void f(int X::*v, X* x) { (x->*v) = 66; }

int main() {
  int X::*n = &X::x;
  X x;
  std::cout << x.x << '\n';  // 1
  int& v = (x.*n);
  v = 100;
  std::cout << x.x << '\n';  // 100

  f(&X::x, &x);
  std::cout << x.x << '\n';  // 66
}