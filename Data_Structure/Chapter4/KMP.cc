#include "KMP.h"

#include <cstring>
#include <fstream>

Status StrAssign(SString T, char *chars) {
  if (strlen(chars) > MAXSTRLEN) {
    return ERROR;
  } else {
    T[0] = strlen(chars);
    for (int i = 1; i <= T[0]; ++i) {
      T[i] = *(chars + i - 1);
    }
    return OK;
  }
}

//算法4.1　BF算法
int Index(SString S, SString T, int pos) {
  //返回模式T在主串S中第pos个字符之后第s一次出现的位置。若不存在，则返回值为0
  //其中，T非空，1≤pos≤StrLength(S)
  int i = pos;
  int j = 1;
  while (i <= S[0] && j <= T[0]) {
    if (S[i] == T[j]) {
      ++i, ++j;
    } else {
      i = i - j + 2;
      j = 1;
    }
  }
  if (j > T[0]) {
    return i - T[0];
  }
  return 0;
}

//算法4.2　KMP算法
int Index_KMP(SString S, SString T, int pos, int next[]) {
  // 利用模式串T的next函数求T在主串S中第pos个字符之后的位置的KMP算法
  //其中，T非空，1≤pos≤StrLength(S)
  int i = pos, j = 1;
  while (i <= S[0] && j <= T[0]) {
    if (j == 0 || S[i] == T[j]) {
      ++i, ++j;
    } else {
      j = next[j];
    }
  }
  if (j > T[0]) {
    return i - T[0];
  }
  return 0;
}

//算法4.3　计算next函数值
void get_next(SString T, int next[]) {
  //求模式串T的next函数值并存入数组next
  int i = 1, j = 0;
  next[1] = 0;
  while (i < T[0]) {
    if (j == 0 || T[i] == T[j]) {
      ++i, ++j;
      next[i] = j;
    } else {
      j = next[j];
    }
  }
}

//算法4.4　计算next函数修正值
void get_nextval(SString T, int nextval[]) {
  // 求模式串T的next函数修正值并存入数组nextval
  int i = 1, j = 0;
  nextval[1] = 0;
  while (i < T[0]) {
    if (j == 0 || T[i] == T[j]) {
      ++i, ++j;
      if (T[i] != T[j]) {
        nextval[i] = j;
      } else {
        nextval[i] = nextval[j];
      }
    } else {
      j = nextval[j];
    }
  }
}

int Index_BF(HString S, HString T, int pos) {
  //返回模式T在主串S中第pos个字符开始第一次出现的位置。若不存在，则返回值为0
  //其中，T非空，1≤pos≤StrLength(S)
  int i, j;
  i = pos;
  j = 1;
  while (i <= S.len && j <= T.len) {
    if (S.ch[i] == T.ch[j]) {
      ++i;
      ++j;
    }  //继续比较后继字符
    else {
      i = i - j + 2;
      j = 1;
    }  //指针后退重新开始匹配
  }
  if (j > T.len)
    return i - T.len;
  else
    return 0;
}

//算法4.5 病毒感染检测（BF）
void Virus_detection() {
  int num, m, flag;
  char Vir[600];
  HString Virus, Person, temp;
  ifstream inFile("Virus_detection.txt");
  ofstream outFile("Virus_detection_Ans.txt");
  inFile >> num;
  while (num--) {
    inFile >> (Virus.ch + 1);
    inFile >> (Person.ch + 1);
    strcpy(Vir, Virus.ch);
    Virus.len = strlen(Virus.ch) - 1;
    Person.len = strlen(Person.ch) - 1;
    flag = 0;
    m = Virus.len;
    for (int i = m + 1, j = 1; j <= m; ++j) {
      //因病毒为环状，故将病毒的长度扩大2倍
      //即可线性取到所有长度为Virus.len的字符串
      Virus.ch[i++] = Virus.ch[j];
    }
    Virus.ch[2 * m + 1] = '\0';
    for (int i = 0; i < m; i++) {
      for (int j = 1; j <= m; j++) {
        temp.ch[j] = Virus.ch[i + j];
      }
      temp.ch[m + 1] = '\0';
      temp.len = strlen(temp.ch) - 1;
      flag = Index_BF(Person, temp, 1);
      if (flag) {
        break;
      }
    }
    if (flag) {
      outFile << Vir + 1 << " " << Person.ch + 1 << " "
              << "YES" << endl;
    } else {
      outFile << Vir + 1 << " " << Person.ch + 1 << " "
              << "NO" << endl;
    }
  }
}

int main() {
  SString S;
  StrAssign(S, (char *)"bbaaabbaba");
  SString T;
  StrAssign(T, (char *)"abb");
  // cout << "主串和子串在第" << Index(S, T, 1) << "个字符处首次匹配\n";
  int *p = new int[T[0] + 1];
  // get_next(T, p);
  get_nextval(T, p);
  // cout << "主串和子串在第" << Index_KMP(S, T, 1, p) << "个字符处首次匹配\n";

  Virus_detection();

  return 0;
}