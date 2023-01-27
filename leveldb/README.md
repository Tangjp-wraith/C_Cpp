# leveldb --version:1.23

## [Slice](https://github.com/Tangjp-wraith/C_Cpp/blob/master/leveldb/include/leveldb/slice.h)

切片是leveldb中的一种数据结构，同redis一样，并没有直接使用string，而是基于底层的c数组做了一层封装，也就是现在的切片。

实现手段与[String](https://github.com/Tangjp-wraith/C_Cpp/tree/master/String)没有太多差别

Slice中大量使用了memcmp，内部[实现](https://github.com/Tangjp-wraith/C_Cpp/tree/master/memcmp)已给出

测试程序TestSlice已在test目录下给出

## [arena](https://github.com/Tangjp-wraith/C_Cpp/blob/master/leveldb/util/arena.h)


