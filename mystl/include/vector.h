#pragma once

#include <stdlib.h>

#include <cstddef>

#include "allocator.h"
#include "constructor.h"
#include "type_traits.h"

namespace mystl {

template <typename T>
class vector {
 public:
  /*---------嵌套类型别名---------*/
  typedef size_t size_type;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef const T& const_reference;
  // vector的iterator用原生指针就可以了,不需要封装，直接指定原生指针为vector的iterator
  typedef pointer iterator;

 protected:
  iterator start;                       //表示当前使用空间的头
  iterator finish;                      //表示当前使用空间的尾
  iterator end_of_storage;              //表示当前可用空间的尾
  typedef allocator<T> data_allocator;  //表示空间配置器

  //辅助函数，这个函数的主要作用就是扩容，newcapacity 应当大于 size()
  void allocate_and_copy(size_type newcapacity) {
    //可用空间为0，则需要重新申请更大可用空间，并把元素都复制过去
    iterator temp = new value_type[newcapacity];
    for (size_type i = 0; i < size(); ++i) {
      if (type_bool<
              typename type_traits<T>::has_trivial_copy_constructor>::value) {
        temp[i] = start[i];
      } else {
        //在指定空间上构造对象
        construct(temp + i, start[i]);
        //析构start + i上的对象
        destroy(start + i);
      }
    }
    //通过空间配置器回收空间
    data_allocator::deallocate(start);
    end_of_storage = temp + (size() * 2);
    finish = temp + size();
    delete start;
    start = temp;
  }

 public:
  /*---------迭代器相关函数---------*/
  iterator begin() const { return start; }

  iterator end() const { return finish; }

  /*---------构造器与析构器相关函数---------*/

  //默认构造器调用带参构造器必须使用委托构造语法，默认初始容量为16
  vector() : vector(16) {}

  vector(int n) {
    start = data_allocator::allocate(n);
    finish = start;
    end_of_storage = start + n;
    for (int i = 0; i < n; ++i) {
      if (type_bool<typename type_traits<T>::has_trivial_default_constructor>::
              value) {
        start[i] = 0;
      } else {
        construct(start + i);
      }
    }
  }

  //参数类型为常量引用，即可以接受常量作为参数又可以接受变量作为参数
  vector(size_type n, const_reference value) {
    start = data_allocator::allocate(n);
    finish = start + n;
    end_of_storage = finish;
    for (int i = 0; i < n; ++i) {
      if (type_bool<
              typename type_traits<T>::has_trivial_copy_constructor>::value) {
        start[i] = value;
      } else {
        construct(start + i, value);
      }
    }
  }

  vector(const vector<T>& vec) {
    for (size_type i = 0; i < size(); ++i) {
      if (!type_bool<
              typename type_traits<T>::has_trivial_copy_constructor>::value) {
        //如果需要就析构start + i上的对象
        destroy(start + i);
      }
      //通过空间配置器回收空间
      data_allocator::deallocate(start);
      start = data_allocator::allocate(vec.capacity());
      finish = start + vec.size();
      end_of_storage = start + vec.capacity();
      //再申请空间
      for (size_type i = 0; i < vec.size(); ++i) {
        if (!type_bool<
                typename type_traits<T>::has_trivial_copy_constructor>::value) {
          start[i] = *(vec.begin() + i);
        } else {
          construct(start + i, *(vec.begin() + i));
        }
      }
    }
  }

  vector(vector && vec){
    
  }

  ~vector() { delete start; }

  int size() const { return int(finish - start); }

  int capacity() const { return int(end_of_storage - start); }

  bool empty() const { return begin() == end(); }

  T& front() { return *begin(); }

  T& back() { return *(end() - 1); }

  reference operator[](int n) { return *(begin() + n); }

  void push_back(const T& x) {
    if (finish == end_of_storage) {
      allocate_and_copy(capacity() * 2);  //这里采用扩容系数为2
    }
    *finish = x;  //在新的finish位置上插入元素
    ++finish;     // finish自增，指针移动
  }

  void pop_back() { --finish; }

  void erase(iterator position) {
    for (iterator i = position; i != finish; ++i) {
      *i = *(i + 1);
    }
    --finish;
  }

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

  void resize(int new_size) { resize(new_size, 0.0); }

  void clear() { erase(begin(), end()); }
};
}  // namespace mystl