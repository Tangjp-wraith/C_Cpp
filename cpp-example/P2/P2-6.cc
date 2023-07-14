#include <iostream>

using namespace std;

struct X {
  int n1 = 6;
  static const int a = 6;
  // 默认实参中不能使用非静态的类成员（即使它们不被求值)
  // 除非用于构成成员指针或在成员访问表达式中使用。
  // void f(int n = n1) { std::cout << n << '\n'; }
  void f(int n = sizeof + n1) { std::cout << n << '\n'; }
  void f_(int n = a) { std::cout << n << '\n'; }
};

int main() {
  X().f();
  X().f_();
}