#include <exception>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <system_error>
#include <thread>
#include <vector>

int n{};
std::mutex m;
std::once_flag f1;

void f() {
  std::lock_guard<std::mutex> lc(m);
  n++;
  std::cout << n << "\n";
  throw std::runtime_error("fuck");
}

void f2() {
  std::lock_guard<std::mutex> lc(m);
  n++;
  std::cout << n << "\n";
}
int main() {
  // 异常是特殊情况，若该调用抛异常，则传播异常给 call_once 的调用方，并且不翻转
  // flag，以令其他调用将得到尝试 ，下例中会调用两次
  // try {
  //   std::call_once(f1, f);
  // } catch (const std::exception&) {
  // }
  // try {
  //   std::call_once(f1, f);
  // } catch (const std::exception&) {
  // }
  // 保证只调用一次
  std::vector<std::thread> v;
  v.emplace_back([] { std::call_once(f1 ,f2); });
  v.emplace_back([] { std::call_once(f1, f2); });
  v.emplace_back([] { std::call_once(f1, f2); });
  v.emplace_back([] { std::call_once(f1, f2); });
  for(auto& i:v) {
    i.join();
  }
}