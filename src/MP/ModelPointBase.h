#ifndef MODEL_POINT_BASE_H_
#define MODEL_POINT_BASE_H_

#include "IModelPoint.h"

class ModelPointBase : public IModelPoint {
public:
  ModelPointBase(const char *name, bool isValid = false);

  const char  *getName() const override;
  unsigned int getSequenceNumber() const override;

  unsigned int touch() override;

  bool         isNotValid(unsigned int *seqNumPtr = 0) const override;
  unsigned int setInvalid(LockRequest lockRequest = eNO_REQUEST) override;

  bool         isLocked() const override;
  unsigned int setLockState(LockRequest lockRequest) override;

protected:
  bool _isValid;

  unsigned int _updateSequenceNumber();
  bool         _testAndUpdateLock(LockRequest lockRequest);

private:
  const char  *_name;
  unsigned int _sequenceNumber;
  bool         _isLocked;
};

#endif
