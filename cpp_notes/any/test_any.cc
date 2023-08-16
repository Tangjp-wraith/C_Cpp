#include <iostream>
#include <vector>

#include "any.hpp"

struct Student {
  Student() = default;
  Student(int id, std::string name) : id_(id), name_(std::move(name)) {}
  int id_{};
  std::string name_;
};

void test_any() {
  any t = "你好";
  auto test_construct = [&]() {
    std::cout << t.type().name() << "\n";

    t = 345456;
    std::cout << t.type().name() << "\n";
    t = Student();
    std::cout << t.type().name() << "\n";
    t = any(Student());
    std::cout << t.type().name() << "\n";
    t = std::move(any("hello我k$"));
  };

  auto test_cast = [&]() {
    std::cout << any_cast<const char*>(t) << "\n";
    t = std::to_string(43324324);
    std::cout << "typename: " << t.type().name()
              << " value: " << any_cast<std::string>(t) << "\n";
  };

  auto test_other = [&]() {
    t.emplace<Student>(323, std::string("fdfsafsda"));
    std::cout << "id: " << any_cast<Student>(t).id_
              << " name: " << any_cast<Student>(t).name_ << "\n";
    t.reset();
    std::cout << t.type().name() << "\n";
    t = std::vector<std::string>{"fdsfasddfas", "fsaffafa", "fdsaadsf"};
    std::cout << "type: " << t.type().name()
              << "t: " << any_cast<std::vector<std::string>>(t)[0] << " "
              << any_cast<std::vector<std::string>>(t)[1] << " "
              << any_cast<std::vector<std::string>>(t)[2] << "\n";
    t = "你好";  // const修饰的常量转变量出错
    std::cout << any_cast<char*>(t) << "\n";
  };
  test_construct();
  test_cast();
  test_other();
}

int main() { test_any(); }