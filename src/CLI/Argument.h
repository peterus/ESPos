#ifndef ARGUMENT_H_
#define ARGUMENT_H_

#include "StringCLI.h"

enum ARGUMENT_TYPE {
  INTEGER,
  STRING,
};

class Argument {
public:
  Argument(ARGUMENT_TYPE type, const String &name, const String &help);
  virtual ~Argument();

  String        getName() const;
  ARGUMENT_TYPE getType() const;

private:
  ARGUMENT_TYPE _type;
  const String  _name;
  const String  _help;
};

class IntegerArgument : public Argument {
public:
  IntegerArgument(const String &name, const String &help);

  int getValue(const String &arg);

private:
};

class StringArgument : public Argument {
public:
  StringArgument(const String &name, const String &help);

  String getValue(const String &arg);

private:
};

#endif
