#include <gtest/gtest.h>

#include "MP/ModelPoint.h"
#include "MP/SubscriberComposer.h"

ModelPoint<bool> _b_modelpoint("boolean");

class testsub {
public:
  testsub() : _shouldRun(*this, &testsub::test_function), _seq_nr(0), _function_called(0) {
  }

  void start() {
    _b_modelpoint.attachSubscriber(_shouldRun);
  }

  void test_function(ModelPoint<bool> &mp) {
    ASSERT_EQ(mp.getSequenceNumber(), _seq_nr);
    _function_called++;
  }

  void set_seq_nr(const unsigned int i) {
    _seq_nr = i;
  }

  unsigned int getFunctionCalled() const {
    return _function_called;
  }

private:
  SubscriberComposer<testsub, ModelPoint<bool>> _shouldRun;
  unsigned int                                  _seq_nr;
  unsigned int                                  _function_called;
};

TEST(Subscriber, basic) {
  testsub obj;
  obj.start();
  obj.set_seq_nr(1);
  _b_modelpoint.setValue(true);
  ASSERT_EQ(obj.getFunctionCalled(), 1);

  obj.set_seq_nr(2);
  _b_modelpoint.setValue(false);
  ASSERT_EQ(obj.getFunctionCalled(), 2);

  obj.set_seq_nr(3);
  _b_modelpoint.setValue(true);
  ASSERT_EQ(obj.getFunctionCalled(), 3);
}
