#ifndef HELP_PRINTER_H_
#define HELP_PRINTER_H_

#include <list>

#include <Arduino.h>

class Command;
class Argument;

class HelpPrinter {
public:
  HelpPrinter(Stream &stream);

  void printCommandList(const std::list<Command *> &commands, const bool is_subcommand = true);
  void printArgumentList(const std::list<Argument *> &commands);

private:
  Stream &_stream;

  template <class T> unsigned int calcMaxLength(const std::list<T> &printable, unsigned int startMaxLength) {
    unsigned int maxLength = startMaxLength;
    for (auto command : printable) {
      unsigned int length = command->getName().length();
      if (length > maxLength) {
        maxLength = length;
      }
    }
    maxLength += 4;
    return maxLength;
  }

  void printCmd(Command const *const command, const unsigned int maxLength);
  void printArg(Argument const *const argument, const unsigned int maxLength);
};

#endif
