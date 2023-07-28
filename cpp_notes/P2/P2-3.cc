#include <iostream>

using namespace std;

class C {
  void f(int i = 3);
  void g(int i, int j = 99);
  C(int arg);  // 非默认构造函数
};

// void C::f(int i = 3) {}  //重定义默认实参

void C::g(int i = 88, int j) {}

// C::C(int arg = 1) {}  //C::C添加默认实参是让它变成了默认构造函数