#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

/*
explicit lock_guard(mutex_type& __m) : _M_device(__m) { _M_device.lock(); }

lock_guard(mutex_type& __m, adopt_lock_t) noexcept
    : _M_device(__m) {}  // calling thread owns mutex
*/

void f() {
  // ...
  mtx.lock();
  // mtx.unlock();
  // ...
  // adopt_lock 占位后 构造函数内不上锁 看上述注释
  std::lock_guard<std::mutex> lock(mtx, std::adopt_lock);
  // 返回实现支持的并发线程数
  std::cout << std::thread::hardware_concurrency() << "\n"; 
  std::cout << "func\t"
            << "f\n";
}

int main() {
  std::thread t(f);
  t.join();
}