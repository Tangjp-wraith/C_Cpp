# 数据结构（C语言版 第2版）严蔚敏

考研数据结构复习

## 如何编译调试运行

在主目录下执行

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=DEBUG ..
make -j$(nproc)  
cd ../ChapterX
./bin/<Executable File>   // CMakeLists.txt 下可查看可执行文件名称 或 bin目录下
```

也可使用Vscode + CMake插件一键编译，运行（运行需要将有些涉及到文件输入的文件放入bin文件夹内）

调试可以使用 Vscode + CodeLLDB插件 进行断点调试，自行配置launch.json

编译、调试、运行环境：g++/clang && CMake && CodeLLDB

## 课本示例代码

完成教材中的示例代码，[目录](https://github.com/Tangjp-wraith/C_Cpp/blob/master/Data_Structure/Sample_dir.md)

## 课后算法设计题

完成教材中每单元课后算法设计题，[目录](https://github.com/Tangjp-wraith/C_Cpp/blob/master/Data_Structure/Homework.md)
