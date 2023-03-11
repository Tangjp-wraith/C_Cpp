#include <iostream>

using namespace std;

// P2-1的例外 ：该形参是从某个形参包展开得到的或是函数形参包

template <class... T>
struct X {
  void f(int n = 0, T...) { std::cout << n << '\n'; };
};
template <class... Args>
void f_(int n = 6, Args... args) {}
int main() {
  X().f();
  X<int>().f(1, 2);  //实例化了X::f(int n=0,int)
}