#include <iostream>

using namespace std;

// 需要在当前作用域提前给你已经声明了默认实参的形参后面的形参默认实参
// 下例中交换位置会报错

void f(int, int, int = 10);
void f(int, int = 6, int);
void f(int = 4, int, int);
void f(int a, int b, int c) {
  std::cout << a << " " << b << " " << c << std::endl;
}

int main(){
  f();
}