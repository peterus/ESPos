#include "Argument.h"

Argument::Argument(ARGUMENT_TYPE type, const String &name, const String &help) : _type(type), _name(name), _help(help) {
}

Argument::~Argument() {
}

String Argument::getName() const {
  return _name;
}

ARGUMENT_TYPE Argument::getType() const {
  return _type;
}

IntegerArgument::IntegerArgument(const String &name, const String &help) : Argument(ARGUMENT_TYPE::INTEGER, name, help) {
}

int IntegerArgument::getValue(const String &arg) {
  return 0;
}

StringArgument::StringArgument(const String &name, const String &help) : Argument(ARGUMENT_TYPE::STRING, name, help) {
}

String StringArgument::getValue(const String &arg) {
  return arg;
}
