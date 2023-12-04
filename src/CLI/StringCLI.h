#ifndef STRING_CLI_H_
#define STRING_CLI_H_

#if defined(ARDUINO)
#include <Arduino.h>
#else
#include <cstring>
#include <string>
typedef std::string String;
inline String       F(String s) {
  return s;
};
#endif

#endif
