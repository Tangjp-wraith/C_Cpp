#include <array>
#include <cstring>
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
  A(std::initializer_list<int> a) {
    std::cout << "C(std::initializer_list<int> a)" << std::endl;
    for (const int *item = a.begin(); item != a.end(); ++item) {
    }
  }
};

void fun1(A arg) {}

A fun2() { return A(10, 5); }

A fun3() { return {10, 5}; }

// void f(double value) { int i(int(value)); }

struct Timer {};

struct TimerKeeper {
  TimerKeeper(Timer t) {}
};

class MyStringWithIndex : public std::string {
 public:
  int index = 0;
};

struct S {
  int x;
  int y;
};

template <typename T, size_t N>
struct MyArray {
  T data[N];
};

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

  // TimerKeeper time_keeper(Timer());
  TimerKeeper time_keeper{Timer()};

  // MyStringWithIndex s{{"hello world!"}, 1};
  // MyStringWithIndex q{"hello world!", 1};
  // std::cout << s.index << std::endl;
  int a1[3]{1, 2, 3};  // 简单类型，原生数组
  int a2[3] = {1, 2, 3};
  std::array<int, 3> a3{1, 2, 3};      // 简单类型，std::array
  std::array<int, 3> a4 = {1, 2, 3};   // 简单类型，std::array
  S a5[3] = {{1, 2}, {3, 4}, {5, 6}};  // 复合类型，原生数组
  S a6[3] = {1, 2, 3, 4, 5, 6};        // 大括号的省略
  // 复合类型，std::array，编译失败！
  // std::array<S, 3> a7{{1, 2}, {3, 4}, {5, 6}}; // 报错
  std::array<S, 3> a7{{{1, 2}, {3, 4}, {5, 6}}};
  std::array<S, 3> a8{1, 2, 3, 4, 5, 6};

  // 报错 也不会调用A(int ,float) 而是调用 A(std::initializer_list<int> a)
  // A aaaa{1, 1.2};
  A aaaaaaa{{}};
  A bbbbbbb({});
}