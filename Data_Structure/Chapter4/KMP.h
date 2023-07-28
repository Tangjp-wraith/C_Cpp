#pragma once

#include <cstring>
#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
#define MAXSTRLEN 255                 //用户可在255以内定义最长串长
typedef char SString[MAXSTRLEN + 1];  // 0号单元存放串的长度

