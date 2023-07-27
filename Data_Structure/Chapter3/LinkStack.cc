#include "LinkStack.h"

//算法3.5　链栈的初始化
Status InitStack(LinkStack &S) {
  S = NULL;
  return OK;
}

//算法3.6　链栈的入栈
Status Push(LinkStack &S, SElemType e) {
  LinkStack p;
  p = new StackNode;
  p->data = e;
  p->next = S;  //将新结点插入栈顶
  S = p;        //修改栈顶指针为p
  return OK;
}

//算法3.7　链栈的出栈
Status Pop(LinkStack &S, SElemType &e) {
  LinkStack p;
  if (S == NULL) {
    return ERROR;
  }
  e = S->data;
  p = S;        //用p临时保存栈顶元素空间，以备释放
  S = S->next;  //修改栈顶指针
  delete p;     //释放原栈顶元素的空间
  return OK;
}

//算法3.8　取链栈的栈顶元素
SElemType GetTop(LinkStack S) {
  if (S != NULL) {
    return S->data;
  }
  return 0;
}

bool StackEmpty(LinkStack S) {
  if (!S) {
    return true;
  }
  return false;
}

// int main() {
//   LinkStack s;
//   int choose, flag = 0;
//   SElemType j, t;
//   cout << "1.初始化\n";
//   cout << "2.入栈\n";
//   cout << "3.读栈顶元素\n";
//   cout << "4.出栈\n";
//   cout << "0.退出\n\n";

//   choose = -1;
//   while (choose != 0) {
//     cout << "请选择:";
//     cin >> choose;
//     switch (choose) {
//       case 1:  //算法3.5　链栈的初始化
//         if (InitStack(s)) {
//           flag = 1;
//           cout << "成功对栈进行初始化\n\n";
//         } else
//           cout << "初始化栈失败\n\n";
//         break;
//       case 2: {  //算法3.6　链栈的入栈
//         fstream file;
//         file.open("SqStack.txt");
//         if (!file) {
//           cout << "错误！未找到文件！\n\n" << endl;
//           exit(ERROR);
//         }
//         if (flag) {
//           flag = 1;
//           cout << "进栈元素依次为：\n";
//           while (!file.eof()) {
//             file >> j;
//             if (file.fail())
//               break;
//             else {
//               Push(s, j);
//               cout << j << "  ";
//             }
//           }
//           cout << endl << endl;
//         } else
//           cout << "栈未建立，请重新选择\n\n";
//         file.close();
//       } break;
//       case 3:  //算法3.8　取链栈的栈顶元素
//         if (flag != -1 && flag != 0)
//           cout << "栈顶元素为：\n" << GetTop(s) << endl << endl;
//         else
//           cout << "栈中无元素，请重新选择\n" << endl;
//         break;
//       case 4:  //算法3.7　链栈的出栈
//         if (flag) {
//           cout << "依次弹出的栈顶元素为:\n";
//           while (Pop(s, t)) cout << t << "  ";
//           cout << endl << endl;
//         } else
//           cout << "栈未建立，请重新选择\n\n";
//         break;
//     }
//   }
//   return 0;
// }

// 算法3.20　数制的转换(链栈实现)
void conversion(int N) {
  //对于任意一个非负十进制数，打印输出与其等值的八进制数
  int e;
  LinkStack S;
  InitStack(S);
  while (N) {
    Push(S, N % 8);
    N = N / 8;
  }
  while (!StackEmpty(S)) {
    // Pop(S, e); // 需要将头文件中SElemType类型改为int
    cout << e;
  }
  cout << endl;
}

// int main() {  //对于输入的任意一个非负十进制数，打印输出与其等值的八进制数
//   int n, e;
//   cout << "输入一个非负十进制数:" << endl;
//   cin >> n;

//   conversion(n);
//   return 0;
// }

// 算法3.21　括号的匹配
bool Matching() {
  char ch;
  SElemType x;
  LinkStack S;
  InitStack(S);
  int flag = 1;
  cin >> ch;
  while (ch != '#' && flag) {  //假设表达式以“#”结尾
    switch (ch) {
      case '[':
      case '(':  //若是左括号，则将其压入栈
        Push(S, ch);
        break;
      case ')':  //若是“)”，则根据当前栈顶元素的值分情况考虑
        if (!StackEmpty(S) && GetTop(S) == '(') {
          Pop(S, x);  //若栈非空且栈顶元素是“(”，则正确匹配
        } else {
          flag = 0;  //若栈空或栈顶元素不是“(”，则错误失败
        }
        break;
      case ']':  //若是“]”，则根据当前栈顶元素的值分情况考虑
        if (!StackEmpty(S) && GetTop(S) == '[') {
          Pop(S, x);  //若栈非空且栈顶元素是“[”，则正确匹配
        } else {
          flag = 0;  //若栈空或栈顶元素不是“[”，则错误匹配
        }
        break;
    }
    cin >> ch;
  }
  if (StackEmpty(S) && flag) {
    return true;
  } else {
    return false;
  }
}

// int main() {
//   LinkStack S;
//   cout << "请输入待匹配的表达式，以“#”结束：" << endl;
//   int flag = (int)Matching();
//   if (flag)
//     cout << "括号匹配成功！" << endl;
//   else
//     cout << "括号匹配失败！" << endl;
//   return 0;
// }

//判断ch是否为运算符
bool In(char ch) {
  for (int i = 0; i < 7; ++i) {
    if (ch == oper[i]) {
      return true;
    }
  }
  return false;
}

//判断运算符优先级
char Precede(char theta1, char theta2) {
  if ((theta1 == '(' && theta2 == ')') || (theta1 == '#' && theta2 == '#')) {
    return '=';
  } else if (theta1 == '(' || theta1 == '#' || theta2 == '(' ||
             (theta1 == '+' || theta1 == '-') &&
                 (theta2 == '*' || theta2 == '/')) {
    return '<';
  } else {
    return '>';
  }
}

//计算两数运算结果
char Operate(char first, char theta, char second) {
  switch (theta) {
    case '+':
      return (first - '0') + (second - '0') + 48;
    case '-':
      return (first - '0') - (second - '0') + 48;
    case '*':
      return (first - '0') * (second - '0') + 48;
    case '/':
      return (first - '0') / (second - '0') + 48;
  }
  return 0;
}

//算法3.22　表达式求值
char EvaluateExpression() {
  //算术表达式求值的算符优先算法，设OPTR和OPND分别为运算符栈和操作数栈
  LinkStack OPTR, OPND;
  char ch, theta, a, b, x, top;
  InitStack(OPND);
  InitStack(OPTR);
  Push(OPTR, '#');  //将表达式起始符“#”压入OPTR栈
  cin >> ch;
  //表达式没有扫描完毕或OPTR的栈顶元素不为“#”
  while (ch != '#' || (GetTop(OPTR) != '#')) {
    if (!In(ch)) {  // ch不是运算符则进OPND栈
      Push(OPND, ch);
      cin >> ch;
    } else {
      //比较OPTR的栈顶元素和ch的优先级
      switch (Precede(GetTop(OPTR), ch)) {
        case '<':
          Push(OPTR, ch);
          cin >> ch;  //当前字符ch压入OPTR栈，读入下一字符ch
          break;
        case '>':
          Pop(OPTR, theta);  //弹出OPTR栈顶的运算符
          Pop(OPND, b);
          Pop(OPND, a);  //弹出OPND栈顶的两个运算数
          Push(OPND, Operate(a, theta, b));
          break;
        case '=':  // OPTR的栈顶元素是“(”且ch是“)”
          Pop(OPTR, x);
          cin >> ch;  //弹出OPTR栈顶的“(”，读入下一字符ch
          break;
      }
    }
  }
  return GetTop(OPND);  // OPND栈顶元素即为表达式求值结果
}

int menu() {
  int c;
  cout << "0-9以内的多项式计算" << endl;
  cout << "1.计算" << endl;
  cout << "0.退出\n" << endl;
  cout << "选择：";
  cin >> c;
  return c;
}

int main() {
  while (1) {
    switch (menu()) {
      case 1: {
        cout << "请输入要计算的表达式(操作数和结果都在0-9的范围内,以#结束):"
             << endl;
        char res = EvaluateExpression();  //算法3.22　表达式求值
        cout << "计算结果为" << res - 48 << endl << endl;
      } 
        break;
      case 0:
        cout << "退出成功\n" << endl;
        exit(0);
      default:
        break;
    }
  }
}