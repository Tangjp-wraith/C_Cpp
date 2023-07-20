#pragma once

//这里负责对象的构造和析构操作，主要是应用placement new

namespace mystl {

template <typename T>
void construct(T* p) {
  new (p) T();
}

template <typename T, typename Value_Type>
void construct(T* p, const Value_Type& value) {
  new (p) T(value);
}

template <typename T>
void destroy(T* p) {
  p->~T();
}

}  // namespace mystl