#include <iostream>

using namespace std;

// operator.*不可以重载，但是operator->*可以重载

struct X {
  void f() { std::cout << "6\n"; }
  template <typename Ty>
  auto operator->*(Ty v) {
    return (this->*v)();
  }
};

int main() {
  X x;
  x->*&X::f;
}