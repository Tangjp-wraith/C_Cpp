#pragma once

//这个头文件包含一个模板类allocator，用于管理内存的分配、释放

#include <stdlib.h>

#include <cstddef>
#include <iostream>
#include <new>

namespace mystl {

template <typename T>
class allocator {
 public:
  typedef size_t size_type;

  static T* allocate() { return static_cast<T*>(::operator new(sizeof(T))); }

  static T* allocate(size_type n) {
    if (n == 0) {
      return nullptr;
    }
    return static_cast<T*>(::operator new(n * sizeof(T)));
  }

  static void deallocate(T* ptr){
    if(ptr == nullptr) {
      return ;
    }
    ::operator delete(ptr);
  }

};

}  // namespace mystl