#include "Command.h"

Command::Command(const String &name, const String &help) : _name(name), _help(help) {
}

Command::~Command() {
}

void Command::addArgument(Argument *const argument) {
  _arguments.push_back(argument);
}

String Command::getName() const {
  return _name;
}

void Command::parse(Stream &stream) {
}
