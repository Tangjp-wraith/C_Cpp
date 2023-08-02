#pragma once
#include <fstream>
#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
// typedef int SElemType; // 3.20
typedef char SElemType;

const char oper[7] = {'+', '-', '*', '/', '(', ')', '#'};

typedef struct StackNode {
  SElemType data;
  struct StackNode *next;
} StackNode, *LinkStack;

//算法3.5　链栈的初始化
Status InitStack(LinkStack &S);

//算法3.6　链栈的入栈
Status Push(LinkStack &S, SElemType e);

//算法3.7　链栈的出栈
Status Pop(LinkStack &S, SElemType &e);

//算法3.8　取链栈的栈顶元素
SElemType GetTop(LinkStack S);

bool StackEmpty(LinkStack S);

//算法3.20　数制的转换(链栈实现)
void conversion(int N);

//算法3.21　括号的匹配
bool Matching();

//判断ch是否为运算符
bool In(char ch);

//判断运算符优先级
char Precede(char theta1, char theta2);

//计算两数运算结果
char Operate(char first, char theta, char second);

//算法3.22　表达式求值
char EvaluateExpression();