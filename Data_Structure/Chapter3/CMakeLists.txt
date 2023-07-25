cmake_minimum_required(VERSION 3.17)

project(Chapter3)

set(CMAKE_CXX_STANDARD 14)

add_executable(SqStack
  SqStack.h
  SqStack.cc
)

add_executable(LinkStack
  LinkStack.h
  LinkStack.cc
)

add_executable(Recursion
  Recursion.h
  Recursion.cc
)

add_executable(SqQueue
  SqQueue.h
  SqQueue.cc
)

add_executable(LinkQueue
  LinkQueue.h
  LinkQueue.cc
)
