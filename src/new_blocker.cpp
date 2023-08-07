#ifndef PIO_UNIT_TESTING
#include <cstddef>

void *operator_new_blocker();

void *operator new(std::size_t size) {
  return operator_new_blocker();
}

void *operator new[](std::size_t size) {
  return operator_new_blocker();
}
#endif
