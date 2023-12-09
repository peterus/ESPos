#ifndef CLI_H_
#define CLI_H_

#include <deque>
#include <list>

#include "Command.h"
#include "StringCLI.h"

class CLI {
public:
  CLI(Stream &stream, const String &appName, bool echo = true, const char prompt = '>');

  void addCommand(Command *const command);

  void start();
  void loop();

private:
  Stream      &_stream;
  const String _appName;
  const char   _prompt;
  bool         _echo;

  std::list<Command *> _commands;
  String               _commandLine;

  void printPrompt();
  void processStream();
  void parse(Stream &stream, std::deque<String> &arguments);
};

std::deque<String> getStringSplitted(String line);

#endif
