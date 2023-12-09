#include <gtest/gtest.h>

#include "CLI/CLI.h"

TEST(LineSplitted_test, basic) {
  String line("this is one line to split");

  std::deque<String> splitted = getStringSplitted(line);

  ASSERT_EQ(splitted.size(), 6);
  ASSERT_STREQ(splitted[0].c_str(), "this");
  splitted.pop_front();
  ASSERT_STREQ(splitted[0].c_str(), "is");
  splitted.pop_front();
  ASSERT_STREQ(splitted[0].c_str(), "one");
  splitted.pop_front();
  ASSERT_STREQ(splitted[0].c_str(), "line");
  splitted.pop_front();
  ASSERT_STREQ(splitted[0].c_str(), "to");
  splitted.pop_front();
  ASSERT_STREQ(splitted[0].c_str(), "split");
  splitted.pop_front();
}
