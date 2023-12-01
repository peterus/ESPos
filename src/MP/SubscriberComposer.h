#ifndef SUBSCRIBER_COMPOSER_H_
#define SUBSCRIBER_COMPOSER_H_

#include "ISubscriber.h"

template <class CONTEXT, class MP> class SubscriberComposer : public ISubscriber<MP> {
public:
  typedef void (CONTEXT::*NotificationFunc_T)(MP &modelPointThatChanged);

  SubscriberComposer(CONTEXT &context, NotificationFunc_T notifyCallback) : _context(context), _notificationCb(notifyCallback) {
  }

  void modelPointChanged(MP &changedModelPoint) noexcept {
    return (_context.*_notificationCb)(changedModelPoint);
  }

private:
  CONTEXT           &_context;
  NotificationFunc_T _notificationCb;
};

#endif
