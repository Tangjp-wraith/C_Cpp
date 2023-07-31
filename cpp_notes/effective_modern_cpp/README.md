# Effective Modern C++

阅读《Effective Modern C++》过程中的写下的一些笔记

其中base是阅读item前的一些补充，item为本书提出的一些条款

Book目录下有本书的中文翻译版

## Deducing Types（ 类型推导）

### base1：顶层const与底层const

> **《C++ Primer》P58：当执行对象拷贝操作时，常量的顶层const不受什么影响，而底层const必须一致**

```cpp
  const int a = 10;
  int b = a;  // 拷贝a的值，顶层const加不加不受影响
  const int *const p = new int(10);
  // int *p1 = p;        // error 底层const必须一致
  // int *const p2 = p;  // error 错误同上
  const int *p3 = p;  // 顶层const可以忽略，但底层必须一致加上了第一个const
  // int *p4 = &a;  // error a虽然是顶层const，&a变成了底层const 注意！！！
  const int *p4 = &a;
  const int &r1 = a;  //常量引用如果在左侧，右侧可以接任何东西
  const int &rr1 = b;  //常量引用如果在左侧，右侧可以接任何东西
  const int &rr2 = 40;  //常量引用如果在左侧，右侧可以接任何东西
  // int &r2 = a;          // error 非常量引用 = 常量
  // int &r3 = r1;  // 引用如果在等号右侧，请忽略& ，错误同上
  int c = a;  // 等于int c = a; 非常量 = 常量引用
```

对于 ` const int *const p = new int(10);`，第一个const为底层const，第二个const为顶层const

(const) p ---> 10(const) , 若pa--->10(const) 显然，如果语句编译通过那*pa=11就可以执行，pa可以直接修改这个10，这是不对的，`int *pa = p`是错误的

而对于 `int *const p = new int(10);`来说，(const) p ---> 10,那么pa--->10是可以的，于是 `int *pa = p`是可以通过的

关于引用&总结如下几点：

- **引用不是对象且不进行拷贝，不满足上面的原则**
- **常量引用如果在左侧，右侧可以接任何东西**
- **非常量引用 = 常量 （报错！！！）**
- **引用如果在等号右侧，请忽略&**
- **非常量 = 常量引用 （正确）**

###  base2：值类型与右值引用

**1、下面函数执行几次拷贝？**

```cpp
int get_x() {
  int a = 10;
  return a;
}
int x = get_x();
```

执行了两次拷贝，即`int tmp = a; int x = temp;`，因此，如果对于类似大内存池进行拷贝构造时，需要进行两次copy，就十分低效

**2、C++98的表达式类型：**

- 左值：指向特定内存的具名对象

- 右值：临时对象，字符串除外的字面量（见base3）

判断一个表达式是左值还是右值：是否可以取地址

```cpp
  // &get_x(); // get_x()返回值是临时对象，是右值，不能取地址
  int y = 10;
  // int *p1 = &y++; // y++ 返回的是临时对象，是右值，错误
  int *p2 = &++y;
```

对于`int *p = &x++;`，对于`x++`可以看为下面这个函数，传入一个引用，返回一个临时值b；因此不可以对其取地址，代码是错的

```cpp
int fun(int &a) {
  int b = a;
  a = a + 1;
  return b;
}
```

对于`int *p = &++x;`，对于`++x`可以看为下面这个函数，传入一个引用，返回该引用；因此可以对其取地址，是正确的

```cpp
int &func(int &a) {
  a = a + 1;
  return a;
}
```

**3、C++11的表达式类型：**

expression（表达式）：

- glvalue（泛左值）
  - lvalue（左值）
  - xvalue（将亡值）
- rvalue（右值）
  - xvalue（将亡值）
  - prvalue（右值）

**4、赋值操作只有拷贝这种唯一解法吗？**

- 拷贝操作
- 引用操作
- 移动操作

**5、右值引用与移动语义：**

左值引用不接受右值，所以出现只接受右值的右值引用 `Type &&`

移动语义：`std::move`可以将左值转为右值，左值的生命周期结束，这个右值被称为将亡值

注意：

- 纯右值也可以`std::move`
- 类中未实现移动构造，`std::move`之后仍是**拷贝**  （**移动语义没移动**），`std::move`还是去我们实现的类中寻找函数，当发现没有移动构造时，由于拷贝构造的const &可以接受任何值，所以进行了拷贝构造
- 右值引用仍是左值
- 右值绑定到右值引用上连移动构造都不会发生

**6、如何得到将亡值：**

- 将泛左值转化为将亡值：
  - `static_cast<type &&>(xxx)`
  - `std::move(xxx)` **移动语义没移动**
- 临时量实质化（c++17引入）

```cpp
  // 拷贝操作，getPool()进行两次copy，
  // 注意：需要在没有移动构造的前提下，有移动构造时会进行两次移动构造
  BigMemoryPool aaa = getPool();
  BigMemoryPool bbb = aaa;   //拷贝操作
  BigMemoryPool &ccc = aaa;  // 引用操作
  // 右值绑定到右值引用上连移动构造都不会发生，eee只是aaa的一个别名，操作aaa，eee，ccc是一样的
  BigMemoryPool &&eee = std::move(aaa);
  BigMemoryPool ddd = std::move(aaa);  // 移动操作，此时aaa已经销毁了

  int x = get_x();
  // int &z = 10;  // &z是左值引用,字面量10是右值，左值引用不接受右值
  // int &z = get_x();  // get_x()返回临时对象，错误同上
  int &&zz = 10;  // &&z是右值引用，右值引用接受右值
  // int &&z = x; // 右值引用只能绑定右值，错误
  int &&z = std::move(x);
  &z;  // 右值引用仍是左值
  const int k = 10;
  const int &&kk = std::move(k);  // const &&
```

```cpp
BigMemoryPool get_pool(const BigMemoryPool &pool) { return pool; }

BigMemoryPool make_pool() {
  BigMemoryPool pool;
  return get_pool(pool);
}
BigMemoryPool kkk= make_pool();
```

对于上面这个函数，执行代码时：

如果类中有拷贝构造和移动构造的情况下，会执行一次拷贝两次移动，原因如下：

```cpp
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
// 下面是main函数内
BigMemoryPool kkk = make_pool();
// BigMemoryPool kkk = temp2; 这里发生第二次移动，将temp2赋给kkk
```

如果类中没有实现移动构造，就会执行三次拷贝

注：上述代码运行时，需要在CMakeLists.txt中加入`set(CMAKE_CXX_FLAGS -fno-elide-constructors) #禁止返回值优化` ，否则，执行代码时，不管写不写移动构造，都只会发生一次拷贝，编译器会帮我们做返回值优化

### base3：数组指针与函数指针

**1、数组相关的数据类型**（太复杂了，c++不建议使用[]）

`int array[5] ={0,1,2,3,4};` array的数据类型是int [5]，不是int *

```cpp
int a = 10;
int array[5] = {0, 1, 2, 3, 4};
int *ptr = array;  // 将数组名直接赋值给一个指针会发生【退化】
// int(*ptr2)[5] = array;
int *ptr3[5] = {&a, &a, &a, &a, &a}; // 数组指针（是指针）
// int (*) [5]  指针数组（是数组） 对数组名取地址那么就没有退化这一说
int(*ptr4)[5] = &array;
int(&ref)[5] = array;  // int (&) [5] 数组引用
```

数组名取地址的类型（int 数组指针）**不等于** 数组名的类型（int 指针）

ptr4和ref要加括号的原因是[]的优先级高于*，不加括号就是ptr3那行代码，意思是ptr3是个数组，数组中每个元素的类型是int *，详见《C++ Primer》P147

`"hello world";` 字符串字面量是左值，原因是编译器在第一次创建这个字面量时会把它存放在一个位置，这样之后的每次拷贝就不需要一个个字符重复创建临时对象了，不然字符串很长的话就显得很蠢！

```cpp
  // &"hello world";  // "hello world"类型是const char[12]
  char str[12] = "hello world";
  const char *strr = "hello world";  // 取地址后变成底层const因此前面需要加const
  // 但是不加const也不会报错，但是我们依旧不能修改strrrr的值
  // char *strrr = "hello world"; 
  // strrr[1] = 's'; // 运行时会出现段错误
```

**2、数组名作为参数传递时会发生退化**

下面前三个函数是等价的，传入的参数都是`int *`，与第四个函数不等价，参数类型是`int (*)[5]`

```cpp
void func1(int a[]);
void func2(int *a);
void func3(int a[5]);
void func4(int (*a)[5]);
```

**3、函数相关的数据类型**

```cpp
bool fun(int a, int b) {
  std::cout << "fun" << std::endl;
  return true;
};                             // => bool (int,int); 函数数据类型
bool (*funptr)(int a, int b);  // => bool (*)(int,int); 函数指针数据类型
// 函数指针赋值 bool (*)(int,int); &可以省略
bool (*funptr1)(int, int) = &fun;  // = fun 函数退化成函数指针
// 函数指针使用 *可以省略
bool c = (*funptr1)(1, 2);  // 输出fun
// 函数指针作为形参 *可以省略
void fun2(int c, bool (*funptr)(int, int));
// 函数指针作为返回值 *不可以省略
bool (*fun3(int c))(int, int);
// 函数的引用
bool (&funref)(int, int) = fun;

// main函数内
bool (*funptr)(int, int) = fun;  // 函数退化成函数指针
//funptr = fun;
//funptr = &fun;
bool xx =funptr(1,2); // 输出fun
bool yy = (*funptr)(1, 2); //输出fun
bool (&funRef)(int, int) = fun;
bool zz = funRef(1,2); //输出fun
```

**4、类型别名（typedef/using）**

c++推荐使用using，便于理解

```cpp
typedef int int_name;
int_name xxx = 10;
using int_name = int;

// typedef bool (*fun3Ptr)(int, int); // fun3Ptr ==  bool (*)(int, int)
// typedef bool fun(int, int);        // fun ==  bool (int, int)
using fun3Ptr = bool (*)(int, int);
using fun3xxx = bool(int, int);
// fun3xxx == fun3Ptr* 
fun3Ptr fun6(int c);           // == bool (*fun3(int c))(int, int);
void fun7(int c, fun3Ptr f);   // == void fun2(int c, bool (*funptr)(int, int));
void fun77(int c, fun3xxx f);  // == void fun77(int c, bool fun(int, int));
void fun777(int c,fun3xxx *f); // == fun7
```

