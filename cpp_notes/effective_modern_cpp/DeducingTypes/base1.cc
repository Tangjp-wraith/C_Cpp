#include <iostream>

int main() {
  const int a = 10;
  int b = a; // 拷贝a的值，顶层const不受影响
  const int *const p = new int(10);
  // int *p1 = p; //error 底层const必须一致
  // int *const p2 = p; //error 错误同上
  const int *p3 = p; // 顶层const可以忽略
  // int *p4 = &a; // error a虽然是顶层const，&a变成了底层const
  const int *p4 = &a;

  const int &r1 = a;  //常量引用如果在左侧，右侧可以接任何东西
  // int &r2 = a;        // error 非常量引用 = 常量
  // int &r3 = r1;  // 引用如果在等号右侧，请忽略& ，错误同上
  // int &r4 = 40; // error 非常量引用的初始值必须为左值
  int c= r1; // 等于int c = a; 非常量 = 常量引用
}