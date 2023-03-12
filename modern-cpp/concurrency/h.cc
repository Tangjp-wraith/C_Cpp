#include <iostream> 
#include <thread>
#include <mutex>

std::mutex m,m2;

void f(){
  // 同时锁住两个互斥
  // m.lock();
  // m2.lock();

  // 等价于上面的 std::lock 函数模板，至少需要两个互斥
  std::lock(m,m2);
}

int main(){
  std::thread t;
}