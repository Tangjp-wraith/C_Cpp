project(Chapter7)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/)

add_executable(SSTable SSTable.h SSTable.cc)
add_executable(HashTable HashTable.h HashTable.cc)
add_executable(BTree BTree.h BTree.cc)
