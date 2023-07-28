#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex m, m2;

void f() {
  // 同时锁住两个互斥
  // m.lock();
  // m2.lock();

  // 等价于上面的 std::lock 函数模板，至少需要两个互斥
  std::lock(m, m2);
}

struct Employee {
  Employee(std::string id) : id(id) {}
  std::string id;
  std::vector<std::string> lunch_partners;
  std::mutex m;
  std::string output() const {
    std::string ret = "Employee " + id + " has lunch partners: ";
    for (const auto &partner : lunch_partners) ret += partner + " ";
    return ret;
  }
};

void send_mail(Employee &, Employee &) {
  // 模拟耗时的发信操作
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

void assign_lunch_partner(Employee &e1, Employee &e2) {
  static std::mutex io_mutex;
  {
    std::lock_guard<std::mutex> lk(io_mutex);
    std::cout << e1.id << " and " << e2.id << " are waiting for locks"
              << std::endl;
  }

  {
    // 用 std::scoped_lock 取得二个锁，而无需担心
    // 其他对 assign_lunch_partner 的调用死锁我们
    // 而且它亦提供便利的 RAII 风格机制

    // 和std::lock_guard没啥区别，只是一个可变参数的版本
    std::scoped_lock lock(e1.m, e2.m);
 
    // 等价代码 1 （用 std::lock 和 std::lock_guard ）
    // std::lock(e1.m, e2.m);
    // std::lock_guard<std::mutex> lk1(e1.m, std::adopt_lock);
    // std::lock_guard<std::mutex> lk2(e2.m, std::adopt_lock);

    // 等价代码 2 （若需要 unique_lock ，例如对于条件变量）
    // std::unique_lock<std::mutex> lk1(e1.m, std::defer_lock);
    // std::unique_lock<std::mutex> lk2(e2.m, std::defer_lock);
    // std::lock(lk1, lk2);
    {
      std::lock_guard<std::mutex> lk(io_mutex);
      std::cout << e1.id << " and " << e2.id << " got locks" << std::endl;
    }
    e1.lunch_partners.push_back(e2.id);
    e2.lunch_partners.push_back(e1.id);
  }

  send_mail(e1, e2);
  send_mail(e2, e1);
}

int main() {
  Employee alice("alice"), bob("bob"), christina("christina"), dave("dave");

  // 在并行线程中指派，因为就午餐指派发邮件消耗很长时间
  std::vector<std::thread> threads;
  threads.emplace_back(assign_lunch_partner, std::ref(alice), std::ref(bob));
  threads.emplace_back(assign_lunch_partner, std::ref(christina),
                       std::ref(bob));
  threads.emplace_back(assign_lunch_partner, std::ref(christina),
                       std::ref(alice));
  threads.emplace_back(assign_lunch_partner, std::ref(dave), std::ref(bob));

  for (auto &thread : threads) thread.join();
  std::cout << alice.output() << '\n'
            << bob.output() << '\n'
            << christina.output() << '\n'
            << dave.output() << '\n';
}