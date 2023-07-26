#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "include/vector.h"

using namespace mystl;

TEST(test1, test_vector) {
  vector<double> &vec = *(new vector<double>(4));
  for (int i = 0; i < 10; ++i) {
    vec.push_back(i);
    EXPECT_FLOAT_EQ(i, vec[i]);
  }

  EXPECT_EQ(10, vec.size());
}