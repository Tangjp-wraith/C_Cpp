/**
 * @file helloworld.cpp
 * @author Tang Jiapeng (tangjiapeng0215@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-26
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <cassert>
#include <iostream>

#include "leveldb/db.h"

using namespace std;
using namespace leveldb;

int main() {
  leveldb::DB *db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "testdb", &db);
  assert(status.ok());

  status = db->Put(WriteOptions(), "first", "hello world!");
  assert(status.ok());
  string res;
  status = db->Get(ReadOptions(), "first", &res);
  assert(status.ok());
  cout << res << endl;

  delete db;
  return 0;
}