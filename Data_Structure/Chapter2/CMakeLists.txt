project(Chapter2)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/)

add_executable(Merge Merge.h Merge.cc)
add_executable(SqList SqList.h SqList.cc)
add_executable(LinkList LinkList.h LinkList.cc )
add_executable(DuLinkList DuLinkList.h DuLinkList.cc)
add_executable(Polynomial Polynomial.h Polynomial.cc)