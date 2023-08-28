#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "include/allocator.h"

using namespace mystl;

TEST(test1, alloc_test) {
  allocator<std::string> alloc;
  auto str_ve = alloc.allocate(4);
  auto p = str_ve;
  alloc.construct(p++, "construct");
  EXPECT_EQ(str_ve[0], "construct");
  alloc.destroy(--p);
  alloc.deallocate(str_ve);
}