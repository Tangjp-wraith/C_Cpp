#include <iostream>
#include <thread>

/*----------------------------------------------------------*/
// 利用RAII过程等待线程完结
class thread_guard {
  std::thread& t;

 public:
  explicit thread_guard(std::thread& t_) : t(t_) {}
  ~thread_guard() {
    /* joinabe成员函数的作用在c++官方文档中是返回线程是否是可结合的
    可结合的意思就是，一个线程是否能够被执行Join或者是detch操作，
    因为相同的线程不能被join两次，也不能join完再进行detach，
    同理也不可以被detach两次，所以joinable函数就是判断是否能进行可结合。*/
    if (t.joinable()) {
      t.join();
    }
  }
  thread_guard(thread_guard const&) = delete;
  thread_guard& operator=(thread_guard const&) = delete;
};
/*------------------------------------------------------------*/

// n销毁后，这个引用就会悬空了，引用了已经被销毁的地址就会造成未定义行为
void f(int& i) {
  i++;
  std::cout << i << "\n";
}

void call() {
  int n{};  // n在call函数执行完会销毁
  std::thread t{f, std::ref(n)};
  // t.detach(); // 错误  fix：t.join()
  ::thread_guard t2(t);
  /* 线程分离 和join不同，join会确保线程在join的地方执行完成，如果一直不执行完成
  就会卡在那里，但是detach就不在乎，它不会卡在这里，主线程就不管了
  join一定会让子线程在主线程之前执行完，
  detach不一样，它可能在主线程已经执行完毕后还执行，子线程的资源由运行时库回收
*/
}

int main() { call(); }