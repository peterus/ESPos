#include "ModelPointBase.h"

ModelPointBase::ModelPointBase(const char *name, bool isValid) : _isValid(isValid), _name(name), _sequenceNumber(0), _isLocked(false) {
}

const char *ModelPointBase::getName() const {
  return _name;
}

unsigned int ModelPointBase::getSequenceNumber() const {
  return _sequenceNumber;
}

unsigned int ModelPointBase::touch() {
  return _updateSequenceNumber();
}

bool ModelPointBase::isNotValid(unsigned int *seqNumPtr) const {
  if (seqNumPtr) {
    *seqNumPtr = _sequenceNumber;
  }
  return !_isValid;
}

unsigned int ModelPointBase::setInvalid(LockRequest lockRequest) {
  if (_testAndUpdateLock(lockRequest)) {
    if (_isValid) {
      _isValid = false;
    }
  }
  return _updateSequenceNumber();
}

bool ModelPointBase::isLocked() const {
  return _isLocked;
}

unsigned int ModelPointBase::setLockState(LockRequest lockRequest) {
  if (lockRequest == eLOCK) {
    _isLocked = true;
  } else if (lockRequest == eUNLOCK) {
    _isLocked = false;
  }
  return _updateSequenceNumber();
}

unsigned int ModelPointBase::_updateSequenceNumber() {
  _sequenceNumber++;
  return _sequenceNumber;
}

bool ModelPointBase::_testAndUpdateLock(LockRequest lockRequest) {
  if (lockRequest == eUNLOCK) {
    _isLocked = false;
    return true;
  } else if (lockRequest == eLOCK) {
    _isLocked = true;
    return true;
  } else if (!_isLocked) {
    return true;
  }
  return false;
}
