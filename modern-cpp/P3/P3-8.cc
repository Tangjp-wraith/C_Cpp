#include <iostream> 

using namespace std;

// 数据成员指针存的偏移量

struct X {
  int a, b;
  double d;
};
int main() {
  auto p = &X::a;
  auto p2 = &X::b;
  auto p3 = &X::d;
  std::cout << *reinterpret_cast<int*>(&p) << '\n';   // 0
  std::cout << *reinterpret_cast<int*>(&p2) << '\n';  // 4
  std::cout << *reinterpret_cast<int*>(&p3) << '\n';  // 8
}