/**
 * @file String.cpp
 * @author Tang Jiapeng (tangjiapeng0215@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-22
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "String.h"

String::String() : data_(nullptr), size_(0) {}

String::String(const char* str) { __init(str); }

void String::__init(const char* str) {
  if (!str) {
    data_ = nullptr;
    size_ = 0;
  } else {
    size_ = strlen(str);
    data_ = new char[size_ + 1];
    memcpy(data_, str, size_ + 1);
  }
}

void String::__clean() {
  if (data_ != nullptr) {
    delete[] data_;
  }
  size_ = 0;
}

void String::__swap(String& other) {
  data_ = nullptr;
  data_ = other.data_;
  size_ = other.size_;
  other.data_ = nullptr;
  other.size_ = 0;
}

String::String(const String& other) { __init(other.data_); }

String::~String() { __clean(); }

String& String::operator=(const String& other) {
  if (this != &other) {
    __clean();
    __init(other.data_);
  }
  return *this;
}

String::String(String&& other) noexcept {
  __clean();
  __swap(other);
}

String& String::operator=(String&& other) noexcept {
  if (this != &other) {
    __clean();
    __swap(other);
  }
  return *this;
}

char& String::operator[](size_t index) {
  if (index < size_) {
    return data_[index];
  }
  throw std::out_of_range("Index out of range");
}

bool String::operator==(const String& other) {
  if (size_ != other.size_) {
    return false;
  }
  return strcmp(data_, other.data_) == 0;
}

String String::operator+(const String& other) {
  if (!other.size_) {
    return *this;
  }
  if (!this->size_) {
    return other;
  }
  String str;
  str.size_ = this->size_ + other.size_;
  str.data_ = new char[str.size_ + 1];
  memcpy(str.data_, this->data_, this->size_);
  memcpy(str.data_ + this->size_, other.data_, other.size_);
  str.data_[str.size_] = '\0';
  return str;
}

const char* String::c_str() const { return data_; }

size_t String::length() { return size_; }

std::ostream& operator<<(std::ostream& out, const String& str) {
  if (str.data_ == nullptr) {
    out << "";
  } else {
    out << str.data_;
  }
  return out;
}

std::istream& operator>>(std::istream& in, String& str) {
  std::cout << "Please input string size: ";
  in >> str.size_;
  str.data_ = new char[str.size_ + 1];
  std::cout << "Please input string data: ";
  in >> str.data_;
  size_t len = strlen(str.data_);
  if (len != str.size_) {
    std::cout << "error! data len != size" << std::endl;
    exit(1);
  }
  return in;
}
