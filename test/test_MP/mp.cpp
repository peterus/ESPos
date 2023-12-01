#include <gtest/gtest.h>

#include "MP/ModelPoint.h"

TEST(ModelPoint_test, name) {
  ModelPoint<bool> p("boolean");
  ASSERT_STREQ(p.getName(), "boolean");
}

TEST(ModelPoint_test, init_mp) {
  ModelPoint<bool> p("boolean");
  ASSERT_TRUE(p.isNotValid());
  ASSERT_EQ(p.getSequenceNumber(), 0);
  ASSERT_FALSE(p.isLocked());
}

TEST(ModelPoint_test, first_assign) {
  ModelPoint<bool> p("boolean");

  bool         value  = true;
  unsigned int seq_nr = p.setValue(value);

  ASSERT_EQ(seq_nr, 1);
  ASSERT_FALSE(p.isNotValid());
  ASSERT_EQ(p.getSequenceNumber(), 1);

  ASSERT_TRUE(p.getValue(value, &seq_nr));
  ASSERT_EQ(seq_nr, 1);
  ASSERT_TRUE(value);
}

TEST(ModelPoint_test, second_assign) {
  ModelPoint<bool> p("boolean");

  // first
  bool         value  = true;
  unsigned int seq_nr = p.setValue(value);

  // second
  value  = false;
  seq_nr = p.setValue(value);

  ASSERT_EQ(seq_nr, 2);
  ASSERT_FALSE(p.isNotValid());
  ASSERT_EQ(p.getSequenceNumber(), 2);

  ASSERT_TRUE(p.getValue(value, &seq_nr));
  ASSERT_EQ(seq_nr, 2);
  ASSERT_FALSE(value);
}

TEST(ModelPoint_test, touch) {
  ModelPoint<bool> p("boolean");

  bool         value  = true;
  unsigned int seq_nr = p.setValue(value);
  ASSERT_EQ(seq_nr, 1);

  seq_nr = p.touch();
  ASSERT_EQ(seq_nr, 2);
  ASSERT_EQ(p.getSequenceNumber(), 2);
}

TEST(ModelPoint_test, set_invalid) {
  ModelPoint<bool> p("boolean");

  bool value = true;
  p.setValue(value);

  ASSERT_FALSE(p.isNotValid());

  unsigned int seq_nr = p.setInvalid();
  ASSERT_EQ(seq_nr, 2);
  ASSERT_TRUE(p.isNotValid());

  p.setValue(value);
  ASSERT_FALSE(p.isNotValid());
}

TEST(ModelPoint_test, locking) {
  ModelPoint<bool> p("boolean", false);
  bool             value = true;

  p.applyLock();
  ASSERT_TRUE(p.isLocked());

  p.setValue(true);
  ASSERT_TRUE(p.getValue(value));
  ASSERT_FALSE(value);

  p.setValue(true, eLOCK);
  ASSERT_TRUE(p.getValue(value));
  ASSERT_TRUE(value);

  p.setLockState(eUNLOCK);
  p.setValue(false);

  ASSERT_TRUE(p.getValue(value));
  ASSERT_FALSE(value);
}
