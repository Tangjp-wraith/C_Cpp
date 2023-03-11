#include <iostream>

using namespace std;

// 默认实参中能在不求值语境使用局部变量和之前的形参，sizeof显然是不求值的

int main() {
  int f = 0;
  void f2(int n = sizeof f);
  void f3(int a = 0, int n = sizeof a);
  f2();
  f3();
}

void f2(int n) { std::cout << n << '\n'; }

void f3(int a, int n) { std::cout << a << ' ' << n << '\n'; }