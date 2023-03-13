#include <iostream>
#include <mutex>
#include <thread>
#include <tuple>
#include <vector>

template <class... Mutexes>
class scoped_lock {
 public:
  explicit scoped_lock(Mutexes&... mtxes) : mtxes_(mtxes...) {
    std::lock(mtxes...);
  }
  explicit scoped_lock(std::adopt_lock_t, Mutexes&... mtxes)
      : mtxes_(mtxes...) {}

  ~scoped_lock() noexcept {
    std::apply([](Mutexes&... mtxes) { (..., mtxes.unlock()); }, mtxes_);
  }

  scoped_lock(const scoped_lock&) = delete;
  scoped_lock& operator=(const scoped_lock&) = delete;

 private:
  std::tuple<Mutexes&...> mtxes_;
};

// 全特化
template <>
class scoped_lock<> {
 public:
  explicit scoped_lock() = default;
  explicit scoped_lock(std::adopt_lock_t) noexcept {}
  ~scoped_lock() = default;

  scoped_lock(const scoped_lock&) = delete;
  scoped_lock& operator=(const scoped_lock&) = delete;
};

void f() {
  static std::mutex m1, m2;
  ::scoped_lock sl{m1, m2};
  std::cout << "function\t"
            << "1111\n";
}

int main() {
  // std::scoped_lock 是C++17添加的，用来管理多个互斥量
  //相当于std::lock_guard + std::lock
  std::vector<std::thread> v;
  for (int i = 0; i < 10; i++) {
    v.emplace_back(f);
  }
  for (auto& i : v) {
    i.join();
  }
  // 偏特化版本和之前实现的lock_guard一样
}