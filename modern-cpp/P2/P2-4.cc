#include <iostream>
#include <memory>

using namespace std;

// 虚函数的覆盖函数不会从基类定义获得默认实参，而在进行虚函数调用时，
// 默认实参根据对象的静态类型确定

/**
// 给定
struct B { virtual ~B() {} }; // 多态类型
struct D: B {};               // 多态类型

D d; // 最终派生对象
B* ptr = &d;

// (*ptr) 的静态类型是 B
// (*ptr) 的动态类型是 D
 */

// 静态类型
// 对程序进行编译时分析所得到的表达式的类型被称为表达式的静态类型。程序执行时静态类型不会更改。

// 动态类型
// 如果某个泛左值表达式指代某个多态对象，那么它的最终派生对象的类型被称为它的动态类型。
// 对于纯右值表达式，动态类型始终与静态类型相同。

struct Base {
  virtual void f(int a = 7) { std::cout << "Base " << a << std::endl; }
};
struct Derived : Base {
  void f(int a) override { std::cout << "Derived " << a << std::endl; }
};

int main() {
  std::unique_ptr<Base> ptr{new Derived};
  ptr->f();  // Derived 7
}