/**
 * @file TestSlice.cpp
 * @author Tang Jiapeng (tangjiapeng0215@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <cassert>
#include <iostream>

#include "leveldb/db.h"

using namespace std;
using namespace leveldb;

int main(){

  Slice s;
  const char* p="hello slice";
  Slice sp(p);
  cout<<(s==sp)<<endl;
  cout<<s.size()<<endl;
  cout<<sp.size()<<endl;
  cout<<sp[2]<<endl;
  sp.remove_prefix(2);
  cout<<sp.size()<<endl;
  cout<<sp.data()<<endl;
  cout<<sp[2]<<endl;
  cout<<sp.ToString()<<endl;
  cout<<s.empty()<<endl;
  cout<<sp.empty()<<endl;
  sp.clear();
  cout<<sp.empty()<<endl;

  Slice s1("abc"),s2("ab");
  cout<<s1.compare(s2)<<endl;
  cout<<s1.starts_with(s2)<<endl;
  cout<<s1.starts_with("c")<<endl;

  int a[]={1,2,3};
  int *ptr=a+2;
  cout<<ptr[-1]<<endl;
  ptr=a;
  cout<<ptr[-1]<<endl;
  return 0;
}