#include <iostream>
#include <mutex>
#include <thread>

template <class Mutex>
struct lock_guard {
  explicit lock_guard(Mutex &mtx) : mtx_(mtx) { mtx.lock(); }

  lock_guard(Mutex &mtx, std::adopt_lock_t) : mtx_(mtx) {}

  ~lock_guard() { mtx_.unlock(); }

  lock_guard(const lock_guard &) = delete;
  lock_guard &operator=(const lock_guard &) = delete;

 private:
  Mutex &mtx_;
};
 
std::mutex mtx;

void f() {
  ::lock_guard<std::mutex> lock(mtx);
  std::cout << "function\t"
            << "11111\n";
}

int main() {
  for (int i = 0; i < 10; i++) {
    std::thread t{f};
    std::thread t2{f};
    t.join();
    t2.join();
  }
}