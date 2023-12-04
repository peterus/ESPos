#ifndef COMMAND_H_
#define COMMAND_H_

#include <list>

#include "Argument.h"
#include "StringCLI.h"

class Command {
public:
  Command(const String &name, const String &help);
  virtual ~Command();

  void addArgument(Argument *const argument);

  String getName() const;

  void parse(Stream &stream);

  // virtual void run() = 0;

private:
  const String          _name;
  const String          _help;
  std::list<Argument *> _arguments;
};

#endif
