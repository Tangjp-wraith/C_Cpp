#include <future>
#include <iostream>
#include <thread>

using namespace std::literals;

int f(int n) {
  int t{};
  for (int i = 0; i < n; i++) {
    t += i;
  }
  std::this_thread::sleep_for(5s);
  return t;
}

/*
std::thread 和 std::async 的区别是什么
std::thread 一定会创建线程 如果资源不够的话，会产生错误
std::async 却不一定，他可能不创建线程 也不会产生错误
std::launch::deferred延迟调用，它不会在线程里运行，
他将延迟到，调用get或者wait执行 
std::launch::async 在线程里面执行，是强制的，默认情况是这个,可能创建失败会程序崩溃
std::launch::async | std::launch::deferred 表示是否创建线程由系统调度决定，
如果系统资源紧张，就不会创建
*/

/*
future 配合std::async函数模板，创建一个异步任务，它最常用的成员函数是get和wait
get调用时候，必须执行完毕后拿到返回值的结果，如果线程没有运行完会一直等待，类似join
wait用于等待线程返回，本身并不返回结果，效果和join更像了

*/

// int main() {
//   std::future<int> ret = std::async(f, 10);
//   std::future<int> ret1 = std::async(std::launch::async, f, 10);
//   std::future<int> ret2 = std::async(std::launch::deferred, f, 10);
//   std::future<int> ret3 =
//       std::async(std::launch::async | std::launch::deferred, f, 10);
//   ret.wait();
//   std::cout << ret.get() << "\n";
// }

int main() {
  std::future<int> future = std::async(std::launch::async, []() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 8;
  });

  std::cout << "waiting...\n";
  std::future_status status;
  do {
    status = future.wait_for(std::chrono::seconds(1));
    if (status == std::future_status::deferred) {
      std::cout << "deferred\n";
    } else if (status == std::future_status::timeout) {
      std::cout << "timeout\n";
    } else if (status == std::future_status::ready) {
      std::cout << "ready!\n";
    }
  } while (status != std::future_status::ready);

  std::cout << "result is " << future.get() << '\n';
}