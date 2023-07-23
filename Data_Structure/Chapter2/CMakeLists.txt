cmake_minimum_required(VERSION 3.17)

project(Chapter2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Merge
  Merge.h
  Merge.cc
)

add_executable(SqList
  SqList.h
  SqList.cc
)

add_executable(LinkList
  LinkList.h
  LinkList.cc
)

add_executable(DuLinkList
  DuLinkList.h
  DuLinkList.cc
)

add_executable(Polynomial
  Polynomial.h
  Polynomial.cc
)