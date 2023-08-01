#include <iostream>

struct people {
//  private: // private就不是聚合类了，{}初始化报错
  // people() = default;
  int age;
  std::string name;
  float height;
};

struct A {
  A(int a) { std::cout << "A(int a)" << std::endl; }
  A(int a, int b) { std::cout << "A(int a,int b)" << std::endl; }
  A(const A &a) { std::cout << "A(const A& a)" << std::endl; }
};

void fun1(A arg) {}

A fun2() { return A(10, 5); }

A fun3() { return {10, 5}; }

int main() {
  // A a = 10;    // 一次构造一次拷贝
  // A b(10);     // 一次构造
  // A c = (10);  // 一次构造一次拷贝
  // A d{10};     // 一次构造
  // A e = {10};  // 一次构造
  // d和e是c++11之后提出的 d和e在c++14前等价，14及之后不等价

  // A f = 10, 5; // 只能接收一个参数，错误
  A g(10, 5);     //一次构造
  A gg(10, 5.);   // 不安全
  A i = {10, 5};  // 一次构造
  // A j = {10,5.}; // 报错，不允许缩窄转换
  A j = {10, static_cast<int>(5.)};
  fun1(A(10, 5));  // 一次构造一次拷贝
  fun1({10, 5});   // 一次构造
  A k = fun2();    // 一次构造两次拷贝
  A m = fun3();  //一次构造一次拷贝 最后赋值给m时会拷贝一次，可以用移动构造
  people aa{19, "cxk", 191.};  // 聚合类的初始化 
}