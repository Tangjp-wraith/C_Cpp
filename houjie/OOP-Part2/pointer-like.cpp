#include <iostream>

using namespace std;

template <class T>
class my_shared_ptr {
 public:
  T& operator*() const { return *px; }
  T* operator->() const { return px; }
  my_shared_ptr(T* p) : px(p) {}

 private:
  T* px;
  long* pn;
};