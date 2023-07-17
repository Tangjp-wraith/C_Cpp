#pragma once

namespace mystl {

/*
类型萃取
POD类型（C++的内建数据类型，还有原生指针和C风格的结构体）和复杂数据类型最大的区别是：
构造（默认构造器）、析构、赋值、复制（拷贝构造器）
即default_constructor，destructor，assignment_operator，copy_constructor
复杂数据类型先天缺少这四样（编译器给它加上的先不算），而POD类型先天具备这四样
（POD的这四样是编译器完成的）类型萃取这部分使用结构体模板实现，
最大的好处C风格结构体也是POD，这样就不用管构造和析构的事情了。
*/

// 不用bool类型的原因是因为空结构体不占用内存空间
// bool变量还占用1字节空间
struct true_type {};
struct false_type {};

template <typename T>
struct type_bool;

// 特化my_type_bool，将true_type，false_type变为bool变量
template <>
struct type_bool<true_type> {
  static constexpr bool value = true;
};

template <>
struct type_bool<false_type> {
  static constexpr bool value = false;
};

template <typename Tp>
struct type_traits {
  // has trivial的字面意思是，是否有不重要的，我个人倾向于理解成，是否无需考虑的
  //是否无需考虑默认构造器，非POD需要考虑，因此false
  typedef false_type has_trivial_default_constructor;
  //是否无需考虑拷贝构造器，非POD需要考虑，因此false
  typedef false_type has_trivial_copy_constructor;
  //是否无需考虑赋值操作符，非POD需要考虑，因此false
  typedef false_type has_trivial_assignment_operator;
  //是否无需考虑析构器，非POD需要考虑，因此false
  typedef false_type has_trivial_destructor;
  //不是POD，false
  typedef false_type is_POD_type;
};

template <>
struct type_traits<signed char> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<unsigned char> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<short> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<unsigned short> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<int> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<unsigned int> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<long> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<unsigned long> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<float> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<double> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<long double> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

//原生指针也是POD
template <typename T>
struct type_traits<T*> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

}  // namespace mystl