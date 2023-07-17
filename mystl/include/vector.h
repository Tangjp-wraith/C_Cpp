#pragma once

#include <stdlib.h>

namespace mystl {

template<typename T>
class vector {
 public:
  /*---------嵌套类型别名----------*/
  typedef size_t size_type;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef const T& const_reference;
  // vector的iterator用原生指针就可以了,不需要封装，直接指定原生指针为vector的iterator
  typedef pointer iterator;  

 protected:
  iterator start;           //表示当前使用空间的头
  iterator finish;          //表示当前使用空间的尾
  iterator end_of_storage;  //表示当前可用空间的尾

  //辅助函数，这个函数的主要作用就是扩容，newcapacity 应当大于 size()
  void allocate_and_copy(int newcapacity) {
    //可用空间为0，则需要重新申请更大可用空间，并把元素都复制过去
    iterator temp = new value_type[newcapacity];
    for (int i = 0; i < size(); ++i) {
      temp[i] = start[i];
    }
    end_of_storage = temp + (size() * 2);
    finish = temp + size();
    delete start;
    start = temp;
  }

 public:
  //给出vector当前使用空间的起始地址
  iterator begin() const { return start; }

  //给出vector当前使用空间的结束地址
  iterator end() const { return finish; }

  //默认构造器
  vector() : start(nullptr), finish(nullptr), end_of_storage(nullptr) {}

  //带参构造器，初始化vector的长度为n
  vector(int n) {
    start = new T[n];
    finish = start;
    end_of_storage = start + n;
    for (int i = 0; i < n; ++i) {
      start[i] = 0.0;
    }
  }

  //带参构造器，初始化vector的长度为n，并将这些位置上的数据全部赋值为value
  //参数类型为常量引用，即可以接受常量作为参数又可以接受变量作为参数
  vector(size_type n, const T& value) {
    start = new T[n];
    finish = start;
    end_of_storage = start + n;
    for (int i = 0; i < n; ++i) {
      start[i] = value;
    }
  }

  //析构器
  ~vector() { delete start; }

  // vector中当前有多少个数据
  int size() const { return int(finish - start); }

  // vector中当前最多可以有多少个数据
  int capacity() const { return int(end_of_storage - start); }

  // vector当前是否为空
  bool empty() const { return begin() == end(); }

  // vector中第一个数据
  T& front() { return *begin(); }

  // vector中最后一个数据
  T& back() { return *(end() - 1); }

  //让vector像数组一样，直接通过数组下标的方式取值
  reference operator[](int n) { return *(begin() + n); }

  //在vector的末尾插入一个数据
  void push_back(const T& x) {
    if (finish == end_of_storage) {
      allocate_and_copy(capacity() * 2);  //这里采用扩容系数为2
    }
    *finish = x;  //在新的finish位置上插入元素
    ++finish;     // finish自增，指针移动
  }

  //删除vector末尾的数据
  void pop_back() { --finish; }

  //删除position所指向的数据
  void erase(iterator position) {
    for (iterator i = position; i != finish; ++i) {
      *i = *(i + 1);
    }
    --finish;
  }

  //删除first到last这一段数据
  void erase(iterator first, iterator last) {
    //将后面元素往前移动即可，把last到finish这一段，复制到a开始的空间这里
    int diff = int(last - first);
    int count = 0;
    for (iterator i = last; i != finish; count++) {
      *(first + count) = *(finish + count + diff);
    }
    finish = finish - diff;
  }

  //调整vec的容量，如果调整后的容量大于调整前，则用数据x填充空余部分，
  //如果调整后容量小于调整前，则只保留前new_size位数据
  void resize(int new_size, const T& x) {
    if (new_size < size()) {
      erase(begin() + new_size, end());
    } else {
      if (new_size > capacity()) {
        allocate_and_copy(capacity() * 2);
      }
      for (int i = 0; i < new_size - size(); ++i) {
        *(finish + i) = x;
      }
      finish += new_size - size();
    }
  }

  //用默认值填充，其余与上同
  void resize(int new_size) { resize(new_size, 0.0); }

  //删除vector中全部数据
  void clear() { erase(begin(), end()); }
};
}  // namespace mystl