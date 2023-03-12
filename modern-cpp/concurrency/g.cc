#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

// 1:unique_lock取代lock_guard
// unique_lock是个类模板，工作中，一般lock_guard（推荐使用）；
// lock_guard取代了mutex的lock和nulcok();
// unique_lock比lock_guard灵活很多；效率上差一点，内存多一点

int v = 1;

void critical_section(int change_v) noexcept {
  static std::mutex mtx;
  std::unique_lock<std::mutex> lock(mtx);
  // 执行竞争操作
  v = change_v;
  std::cout << v << std::endl;
  // 将锁进行释放
  lock.unlock();

  // 在此期间，任何人都可以抢夺 v 的持有权

  // 开始另一组竞争操作，再次加锁
  lock.lock();
  v += 1;
  std::cout << v << std::endl;
}

struct X {
  mutable std::mutex mtx;  //互斥量的生存期至少大于管理类
  // 在类中，可能多个函数都依赖这一个互斥量，每个函数都有管理类
  void f() const {
    // mtx.lock(); 可写可不写
    std::unique_lock<std::mutex> ul(mtx, std::adopt_lock);
    std::cout << "22222\t" << std::this_thread::get_id() << "\n";
    ul.unlock();
    // unique_lock能更好的控制类的粒度，更加精细
  }
};

std::mutex m;
// 如果在局部写了管理类，那互斥量起码存储期得大于它，一般写在全局
void f() {
  std::unique_lock<std::mutex> ul(m, std::adopt_lock);
  // ul.lock(); 错误
  std::cout << "1111\t" << std::this_thread::get_id() << "\n";
  ul.unlock();
}

int main() {
  std::thread t1(critical_section, 2),
      t2(critical_section,
         3);  //只有两种可能2334或者3423，这主要看这两个线程谁先开启
  t1.join();
  t2.join();

  std::thread t3(f);
  t3.join();

  X x;
  std::thread t4(&X::f, &x);
  t4.join();
  return 0;
}