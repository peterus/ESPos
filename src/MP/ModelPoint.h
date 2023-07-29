#ifndef MODEL_POINT_H_
#define MODEL_POINT_H_

#include "ModelPointBase.h"

template <typename T> class ModelPoint : public ModelPointBase {
public:
  ModelPoint(const char *name, T value) : ModelPointBase(name, true) {
    setValue(value);
  }

  ModelPoint(const char *name) : ModelPointBase(name, false) {
  }

  unsigned int setValue(const T value, LockRequest lockRequest = eNO_REQUEST) {
    if (_testAndUpdateLock(lockRequest)) {
      _value   = value;
      _isValid = true;
      _updateSequenceNumber();
    }
    return getSequenceNumber();
  }

  bool getValue(T &value, unsigned int *sequenceNumber = 0) {
    if (_isValid) {
      value = _value;
    }
    if (sequenceNumber) {
      *sequenceNumber = getSequenceNumber();
    }
    return _isValid;
  }

private:
  T _value;
};

#endif
