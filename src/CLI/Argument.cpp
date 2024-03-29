#include "Argument.h"

Argument::Argument(ARGUMENT_TYPE type, const String &name, const String &help) : _type(type), _name(String("--") + name), _help(help), _isSet(false) {
}

Argument::~Argument() {
}

String Argument::getName() const {
  return _name;
}

String Argument::getHelp() const {
  return _help;
}

ARGUMENT_TYPE Argument::getType() const {
  return _type;
}

bool Argument::isSet() const {
  return _isSet;
}

void Argument::set(bool isSet) {
  _isSet = isSet;
}

IntegerArgument::IntegerArgument(const String &name, const String &help, long default_value) : Argument(ARGUMENT_TYPE::INTEGER, name, help), _default_value(default_value), _value(default_value) {
}

void IntegerArgument::reset() {
  _value = _default_value;
}

long IntegerArgument::getValue() {
  return _value;
}

String IntegerArgument::getAsString() const {
  return String(_value);
}

void IntegerArgument::parse(Stream &stream, const String &argument) {
  _value = argument.toInt();
}

StringArgument::StringArgument(const String &name, const String &help, const String &default_value) : Argument(ARGUMENT_TYPE::STRING, name, help), _default_value(default_value), _value(default_value) {
}

void StringArgument::reset() {
  _value = _default_value;
}

String StringArgument::getValue() {
  return _value;
}

String StringArgument::getAsString() const {
  return _value;
}

void StringArgument::parse(Stream &stream, const String &argument) {
  _value = argument;
}
