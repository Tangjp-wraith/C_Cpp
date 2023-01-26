PROJECT(Test)
cmake_minimum_required(VERSION 3.20)

set(BASE_INCLUDES /home/tang/CSProjects/C_Cpp/leveldb/include/)
set(BASE_LIBS /home/tang/CSProjects/C_Cpp/leveldb/build/)

include_directories(${BASE_INCLUDES})

link_directories(${BASE_LIBS})
add_executable(hw helloworld.cpp)
target_link_libraries(hw leveldb)

