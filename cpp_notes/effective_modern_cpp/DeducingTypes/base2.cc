#include <algorithm>
#include <cstring>
#include <iostream>
#include <utility>

class BigMemoryPool {
 public:
  static const int PoolSize = 4096;
  BigMemoryPool() : pool_(new char[PoolSize]) {}
  ~BigMemoryPool() {
    if (pool_ != nullptr) {
      delete[] pool_;
    }
  }
  BigMemoryPool(BigMemoryPool &&other) {
    std::cout << "move" << std::endl;
    pool_ = other.pool_;
    other.pool_ = nullptr;
  }
  BigMemoryPool(const BigMemoryPool &other) : pool_(new char[PoolSize]) {
    std::cout << "copy" << std::endl;
    memcpy(pool_, other.pool_, PoolSize);
  }

 private:
  char *pool_;
};

BigMemoryPool getPool() {
  BigMemoryPool memoryPool;
  return memoryPool;
}

BigMemoryPool get_pool(const BigMemoryPool &pool) {
  return pool;  // 这里的pool是个左值
}
// BigMemoryPool temp = pool;
// 退出上面这个函数时，会出现这个临时变量，因为pool是左值，这里发生第一个拷贝

BigMemoryPool make_pool() {
  BigMemoryPool pool;  // 调用无参构造函数什么都不发生
  return get_pool(pool);
}
// BigMemoryPool temp2 = temp; // 由于这里temp是临时变量，所以发生移动

int get_x() {
  int a = 10;
  return a;
}

int main() {
  // &get_x(); // get_x()返回值是临时对象，是右值，不能取地址
  int y = 10;
  // int *p1 = &y++; // y++ 返回的是临时对象，是右值，错误
  int *p2 = &++y;

  // 拷贝操作，getPool()进行两次copy，
  // 注意：需要在没有移动构造的前提下，有移动构造时会进行两次移动构造
  // BigMemoryPool aaa = getPool();
  // BigMemoryPool bbb = aaa;   //拷贝操作
  // BigMemoryPool &ccc = bbb;  // 引用操作
  // //
  // 右值绑定到右值引用上连移动构造都不会发生，eee只是aaa的一个别名，操作aaa，eee，ccc是一样的
  // BigMemoryPool &&eee = std::move(aaa);
  // BigMemoryPool ddd = std::move(aaa);  // 移动操作，此时aaa已经销毁了

  BigMemoryPool kkk = make_pool();
  // BigMemoryPool kkk = temp2; 这里发生第二次移动，将temp2赋给kkk

  int x = get_x();
  // int &z = 10;  // &z是左值引用,字面量10是右值，左值引用不接受右值
  // int &z = get_x();  // get_x()返回临时对象，错误同上
  int &&zz = 10;  // &&z是右值引用，右值引用接受右值
  // int &&z = x; // 右值引用只能绑定右值，错误
  int &&z = std::move(x);
  // &z;  // 右值引用仍是左值
  const int k = 10;
  const int &&kk = std::move(k);  // const &&
}
