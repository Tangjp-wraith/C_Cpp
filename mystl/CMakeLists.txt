cmake_minimum_required(VERSION 3.17)

project(mystl
  LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 14)
set(MYSTL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

find_package(GTest REQUIRED)

add_executable(test
  ${MYSTL_INCLUDE_DIR}
  test.cc
)

target_link_libraries(test
  GTest::GTest
  GTest::Main
)