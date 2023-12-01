#ifndef I_SUBSCRIBER_H_
#define I_SUBSCRIBER_H_

template <typename MP> class ISubscriber {
public:
  virtual ~ISubscriber() {
  }

  virtual void modelPointChanged(MP &changedModelPoint) = 0;
};

#endif
