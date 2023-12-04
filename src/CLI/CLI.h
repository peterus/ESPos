#ifndef CLI_H_
#define CLI_H_

#include <list>

#include "Command.h"
#include "StringCLI.h"

class CLI {
public:
  CLI(const String &appName, const char promt = '>');

  void addCommand(Command *const command);

  void start();

private:
  const String _appName;
  const char   _promt;

  std::list<Command *> _commands;
};

#endif
