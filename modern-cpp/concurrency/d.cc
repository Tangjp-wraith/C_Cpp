#include <iostream>
#include <mutex>
#include <thread>

// 互斥量
std::mutex mtx;

void f1() {
  mtx.lock();
  std::cout << "func1\t"
            << "1111\n";
  mtx.unlock();
}
void f2() {
  mtx.lock();
  std::cout << "func2\t"
            << "2222\n";
  mtx.unlock();
}

int n = 1;

void f3() {
  // 管理类
  std::lock_guard<std::mutex> lock(mtx);
  n++;
}

void f4() {
  std::lock_guard<std::mutex> lock(mtx);
  std::cout << n << "\n";
}

// t t2 运行顺序不一定

int main() {
  for (int i = 0; i < 10; ++i) {
    std::thread t{f3};
    std::thread t2{f4};
    t.join();
    t2.join();
  }
}