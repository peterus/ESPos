#ifndef I_MODEL_POINT_H_
#define I_MODEL_POINT_H_

#include "SubscriberApi.h"

enum LockRequest {
  eNO_REQUEST,
  eLOCK,
  eUNLOCK,
};

class IModelPoint {
public:
  virtual ~IModelPoint() {
  }

  virtual const char  *getName() const           = 0;
  virtual unsigned int getSequenceNumber() const = 0;

  virtual unsigned int touch() = 0;

  virtual bool         isNotValid(unsigned int *seqNumPtr = 0) const     = 0;
  virtual unsigned int setInvalid(LockRequest lockRequest = eNO_REQUEST) = 0;

  virtual bool         isLocked() const                      = 0;
  virtual unsigned int setLockState(LockRequest lockRequest) = 0;
  virtual unsigned int removeLock()                          = 0;
  virtual unsigned int applyLock()                           = 0;
};

#endif
