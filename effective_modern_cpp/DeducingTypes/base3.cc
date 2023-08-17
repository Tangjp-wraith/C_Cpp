#include <iostream>
#include <string>
#include <vector>

void func1(int a[]);
void func2(int *a);
void func3(int a[5]);
void func4(int (*a)[5]);

bool fun(int a, int b) {
  std::cout << "fun" << std::endl;
  return true;
};                             // => bool (int,int); 函数数据类型
bool (*funptr)(int a, int b);  // => bool (*)(int,int); 函数指针数据类型

// 函数指针赋值 bool (*)(int,int); &可以省略
bool (*funptr1)(int, int) = &fun;  // = fun 函数退化成函数指针
// 函数指针使用 *可以省略
bool c = (*funptr1)(1, 2);  // 输出fun
// 函数指针作为形参 *可以省略
void fun2(int c, bool (*funptr)(int, int));
// 函数指针作为返回值 *不可以省略
bool (*fun3(int c))(int, int);
// 函数的引用
bool (&funref)(int, int) = fun;

typedef int int_name;
int_name xxx = 10;
using int_name = int;

// typedef bool (*fun3Ptr)(int, int); // fun3Ptr ==  bool (*)(int, int)
// typedef bool fun(int, int);        // fun ==  bool (int, int)
using fun3Ptr = bool (*)(int, int);
using fun3xxx = bool(int, int);

fun3Ptr fun6(int c);           // == bool (*fun3(int c))(int, int);
void fun7(int c, fun3Ptr f);   // == void fun2(int c, bool (*funptr)(int, int));
void fun77(int c, fun3xxx f);  // == void fun77(int c, bool fun(int, int));
void fun777(int c,fun3xxx *f); // == fun7

int main() {
  int a = 10;
  int array[5] = {0, 1, 2, 3, 4};
  int *ptr = array;  // 将数组名直接赋值给一个指针会发生【退化】
  // int(*ptr2)[5] = array;
  int *ptr3[5] = {&a, &a, &a, &a, &a};  // 数组指针（是指针）
  // int (*) [5]  指针数组（是数组） 对数组名取地址那么就没有退化这一说
  int(*ptr4)[5] = &array;
  int(&ref)[5] = array;  // int (&) [5] 数组引用

  // &"hello world";  // "hello world"类型是const char[12]
  char str[12] = "hello world";
  const char *strr = "hello world";  // 取地址后变成底层const因此前面需要加const
  // 但是不加const也不会报错，但是我们依旧不能修改strrrr的值
  // char *strrr = "hello world";
  // strrr[1] = 's'; // 运行时会出现段错误
  
  bool (*funptr)(int, int) = fun;  // 函数退化成函数指针
  funptr = fun;
  funptr = &fun;
  bool xx =funptr(1,2); // 输出fun
  bool yy = (*funptr)(1, 2); //输出fun
  bool (&funRef)(int, int) = fun;
  bool zz = funRef(1,2); //输出fun
  return 0;
}