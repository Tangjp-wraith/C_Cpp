#include <iostream>
#include <thread>

struct X {
  X() noexcept { puts("默认构造"); }
  X(X&&) noexcept { puts("移动构造"); }
  X(const X&) noexcept { puts("拷贝构造"); }
};

void f(X&& x) {}

auto f2() {
  std::thread t{[](int n) { std::cout << n << "\n"; }, 10};
  return t;
}

void f3() { std::cout << std::this_thread::get_id() << "\n"; }

// 只能使用移动语义移交线程的归属权
int main() {
  // X x;
  // std::thread t{f, std::move(x)}; // 默认构造+移动构造
  // t.join();

  // f2().join();
  std::thread t;
  t = f2(); // 纯右值
  t.join();

  std::thread t2{[](int n) { std::cout << n << "\n"; }, 11};
  std::thread t3 = std::move(t2); //std::move 返回亡值
  t3.join();
  // t2.join(); 错误：t2未关联线程对象
  // std::thread 的拷贝构造delete t3=t2 错误
  t2 = std::thread(f3); // 纯右值
  t2.join();
}