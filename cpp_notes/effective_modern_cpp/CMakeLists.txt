cmake_minimum_required(VERSION 3.17)

project(effectivemoderncpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -fno-elide-constructors) # 禁止返回值优化

add_subdirectory(DeducingTypes)



