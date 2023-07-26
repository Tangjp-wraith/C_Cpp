cmake_minimum_required(VERSION 3.17)

project(mystl)

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(GTest REQUIRED)

add_executable(test
  main.cc
  include/vector.h
  include/allocator.h
  include/constructor.h
  include/type_traits.h
)

target_link_libraries(test
  GTest::GTest
  GTest::Main
)