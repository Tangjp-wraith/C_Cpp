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

int main() {
  char s1[]="abc";
  char s2[]="abcd";
  int res=my_memcmp(s1,s2,4);
  std::cout<<res<<std::endl;
  return 0;
}