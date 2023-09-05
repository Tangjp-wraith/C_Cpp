#pragma once

#include <exception>
#include <memory>
#include <type_traits>
#include <typeinfo>

class bad_cast : std::exception {
  auto what() const noexcept -> const char* override {
    return "bad_cast exception";
  }
};

class any {
  class type_base;
  using DataPtr = std::unique_ptr<type_base>;

  struct type_base {
    type_base() = default;
    virtual ~type_base() = default;
    virtual auto get_typeinfo() const -> const std::type_info& = 0;
    virtual auto clone() const -> DataPtr = 0;
  };

  template <typename T>
  struct type_impl : public type_base {
    type_impl() = default;
    type_impl(T const& data) : data_(data) {}
    type_impl(T&& data) : data_(std::move(data)) {}
    template <class... Args>
    type_impl(Args&&... args) : data_(std::forward<Args>(args)...) {}

    auto get_typeinfo() const -> const std::type_info& override {
      return typeid(T);
    }

    auto clone() const -> DataPtr override {
      return std::unique_ptr<type_impl>(new type_impl(data_));
    }

    T data_;
  };

 public:
  any() = default;
  ~any() = default;
  // 拷贝构造
  any(const any& other) {
    if (other.m_data) {
      m_data = std::move(other.m_data->clone());
    }
  }
  any& operator=(any const& other) {
    if (other.m_data) {
      m_data = std::move(other.m_data->clone());
    }
    return *this;
  }
  // 移动构造
  any(any&& other) : m_data(std::move(other.m_data)) {}
  any& operator=(any&& other) {
    m_data = std::move(other.m_data);
    return *this;
  }

  // 任意类型的存取

  // 数据的存入
  template <typename T>
  using decay = typename std::decay<T>::type;

  template <typename T,
            typename std::enable_if<!std::is_same<decay<T>, any>::value,
                                    bool>::type = true>
  any(T&& data) : m_data(new type_impl<decay<T>>(std::forward<T>(data))) {}
  template <typename T,
            typename std::enable_if<!std::is_same<decay<T>, any>::value,
                                    bool>::type = true>
  any operator=(T&& data) {
    m_data.reset(new type_impl<decay<T>>(std::forward<T>(data)));
    return *this;
  }

  auto has_value() const -> bool { return m_data.operator bool(); }

  auto type() -> const std::type_info& {
    if (has_value()) {
      return m_data->get_typeinfo();
    }
    return typeid(void);
  }

  void reset() noexcept { m_data.reset(); }

  template <class T, class... Args>
  void emplace(Args&&... args) {
    m_data.reset(new type_impl<decay<T>>(std::forward<Args>(args)...));
  }

  // 任意类型的取出
  template <typename T>
  auto cast() const -> T const& {
    if (m_data && check_type<T>()) {
      return static_cast<const type_impl<T>*>(m_data.get())->data_;
    }
    throw bad_cast();
  }

  template <typename T>
  auto cast() -> T& {
    if (m_data && check_type<T>()) {
      return static_cast<type_impl<T>*>(m_data.get())->data_;
    }
    throw bad_cast();
  }

 private:
  template <typename T>
  auto check_type() const -> bool {
    if (typeid(T).hash_code() == m_data->get_typeinfo().hash_code()) {
      return true;
    }
    return false;
  }

  DataPtr m_data;
};

template <class T>
auto any_cast(const any& any) -> const T& {
  return any.template cast<T>();
}

template <class T>
auto any_cast(any& any) -> T& {
  return any.template cast<T>();
}