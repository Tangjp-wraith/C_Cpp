#include <atomic>
#include <iostream>

int main() {
  std::atomic<int> n{1};
  std::atomic_bool flag;  // 别名
  n += 2;
  n--;
  // 不是原子操作，可被打断
  int a{};
  a++;
  a += 5;
}