#include <iostream> 

using namespace std;

// 虚成员函数指针也是偏移量
//这是编译器的实现，标准没有规定这些东西，只规定了行为。

struct X {
  virtual void func() { std::cout << "X\n"; }
};
int main() {
  auto ptr = &X::func;
  auto func = *(int*)(&ptr);
  std::cout << func << '\n';  // 1
}