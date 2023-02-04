#include <iostream>

int my_memcmp(const void *buffer1, const void *buffer2, size_t count) {
  if (count <= 0) {
    return 0;
  }
  while (--count && *(char *)buffer1 == *(char *)buffer2) {
    buffer1 = (char *)buffer1 + 1;
    buffer2 = (char *)buffer2 + 1;
  }
  if (*((unsigned char *)buffer1) - *((unsigned char *)buffer2) > 0) {
    return 1;
  } else {
    return -1;
  }
}

// gcc code
int gcc_memcmp(const void *str1, const void *str2, size_t count) {
  /**register */ const unsigned char *s1 = (const unsigned char *)str1;
  /**register */ const unsigned char *s2 = (const unsigned char *)str2;
  while (count-- > 0) {
    // if中 每次都有++操作，[-1]就是访问前一个字符
    if (*s1++ != *s2++) {
      return s1[-1] < s2[-1] ? -1 : 1;
    }
  }
  return 0;
}

int main() {
  char s1[] = "abc";
  char s2[] = "abcd";
  int res = gcc_memcmp(s1, s2, 4);
  std::cout << res << std::endl;
  return 0;
}