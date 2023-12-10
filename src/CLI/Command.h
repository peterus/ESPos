#ifndef COMMAND_H_
#define COMMAND_H_

#include <deque>
#include <list>

#include <Arduino.h>

#include "Argument.h"
#include "HelpPrinter.h"

class Command {
public:
  Command(const String &name, const String &help);
  virtual ~Command();

  String getName() const;
  String getHelp() const;

  void addSubcommand(Command *const command);
  void addArgument(Argument *const argument);

  void parse(Stream &stream, std::deque<String> &arguments, std::list<Argument *> parsedArguments);

  virtual void run(std::list<Argument *> parsedArguments) = 0;

private:
  const String          _name;
  const String          _help;
  std::list<Command *>  _subCommands;
  std::list<Argument *> _arguments;

  void print_help(Stream &stream) const;
  bool process_argument(Stream &stream, std::deque<String>::iterator &argument_iter);
  void process_subcommand(Stream &stream, std::deque<String>::iterator &argument_iter, std::deque<String> &arguments, std::list<Argument *> parsedArguments);
};

#endif
