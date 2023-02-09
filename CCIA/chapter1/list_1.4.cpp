#include <iostream>
#include <thread>  // 管理线程的函数和类声明在此头文件

void hello(){
  std::cout<<"hello concurrency world"<<std::endl;
}

int main(){
  std::thread t(hello); // t对象拥有新函数hello作为其初始函数
  t.join(); 
}