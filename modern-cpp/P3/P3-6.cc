#include <iostream> 
#include <functional>

using namespace std;

class Test {
 public:
  uint16_t num = 0;
  void f() { std::cout << "66\n"; }
};

int main() {
  Test c;
  uint16_t& i = std::invoke(&Test::num, &c);  //绑定数据成员返回引用
  i = 9999;
  std::cout << c.num << '\n';
  std::invoke(&Test::f, &c);  //直接调用，无返回值
}