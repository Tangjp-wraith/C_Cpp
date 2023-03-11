#include <functional>
#include <iostream>

using namespace std;

struct Test_bind {
  void t(int n) {
    for (; n; n--) std::cout << n << "\n";
  }
  void t() { std::cout << "重载的t\n"; }
};

// 使用static_cast指定类型的成员函数到成员函数指针类型转换来消解函数重载的歧义

int main() {
  Test_bind t_b;
  auto n =
      std::bind(static_cast<void (Test_bind::*)(int)>(&Test_bind::t), &t_b, 3);
  n();
  auto m =
      std::bind(static_cast<void (Test_bind::*)()>(&Test_bind::t), &t_b);
  m();
}