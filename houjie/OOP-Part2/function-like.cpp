#include <iostream>

using namespace std;

template <class T>
class identity {
 public:
  const T& operator()(const T& x) const { return x; }
};

int main() {
  int a = 100;
  // 第一个括号是调用构造函数的括号，第二个括号才是operator()
  int b = identity<int>()(a);
  identity<int> ab;
  int c = ab(a);
  cout << b << endl;
  cout << c << endl;
  return 0;
}