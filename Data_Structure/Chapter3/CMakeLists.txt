project(Chapter3)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/)

add_executable(SqStack SqStack.h SqStack.cc)
add_executable(LinkStack LinkStack.h LinkStack.cc)
add_executable(Recursion Recursion.h Recursion.cc)
add_executable(SqQueue SqQueue.h SqQueue.cc)
add_executable(LinkQueue LinkQueue.h LinkQueue.cc)
