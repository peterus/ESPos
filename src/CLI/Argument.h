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
  String        getHelp() const;
  ARGUMENT_TYPE getType() const;
  bool          isSet() const;

  virtual void reset() = 0;

  virtual String getAsString() const = 0;

  virtual void parse(Stream &stream, const String &argument) = 0;

protected:
  void set(bool isSet = true);

private:
  ARGUMENT_TYPE _type;
  const String  _name;
  const String  _help;

  bool _isSet;
};

class IntegerArgument : public Argument {
public:
  IntegerArgument(const String &name, const String &help);

  void reset() override;
  long getValue();

  String getAsString() const override;

  void parse(Stream &stream, const String &argument) override;

private:
  long _value;
};

class StringArgument : public Argument {
public:
  StringArgument(const String &name, const String &help);

  void   reset() override;
  String getValue();

  String getAsString() const override;

  void parse(Stream &stream, const String &argument) override;

private:
  String _value;
};

#endif
