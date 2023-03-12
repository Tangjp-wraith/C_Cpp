#include <chrono>
#include <cstddef>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

using namespace std::literals::chrono_literals;

void f(int &t, size_t n) {
  size_t tmp{};
  for (int i = 1; i < n; i++) {
    tmp += i;
  }
  t = tmp;
}

struct F {
  auto operator()() { std::cout << std::this_thread::get_id() << "\n"; }
};

int main() {
  std::thread t{[]() { std::cout << std::this_thread::get_id() << "\n"; }};
  //	joinable 检查线程是否可合并，即潜在地运行于平行环境中
  std::cout << t.joinable() << "\n";
  // join 等待线程完成其执行
  t.join();
  // if (t.joinable()) {
  //   t.join();
  //   std::cout << t.joinable() << "\n";
  // }
  std::cout << t.joinable() << "\n";
  int v{};
  std::thread t2{f, std::ref(v), 100};
  // 这个实现有invoke检测
  // C++11的设计者认为应该默认按照值传递，而不是引用 比如 std::thread
  // std:function 就算你的可调用对象写了这个引用的形参，需要std::ref()
  t2.join();
  std::cout << v << "\n";

  // std::thread t3(F()); // 错误：会认为F()是一个函数声明 
  // int f(int()) -> int f(int (*g)()) 会识别成函数指针
  std::thread t3{F()};
  t3.join();
  std::thread t4((F()));
  t4.join();

  std::cout << "------------------------\n";
  std::vector<std::thread> Threads;
  for (size_t i = 0; i < 10; i++) {
    Threads.emplace_back(
        []() { std::cout << std::this_thread::get_id() << "\n"; });
  }
  for (auto &i : Threads) {
    i.join();
  }

  std::this_thread::sleep_for(10s);
}