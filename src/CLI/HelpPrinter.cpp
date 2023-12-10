#include "HelpPrinter.h"

#include "Argument.h"
#include "Command.h"

HelpPrinter::HelpPrinter(Stream &stream) : _stream(stream) {
}

void HelpPrinter::printCommandList(const std::list<Command *> &commands, const bool is_subcommand) {
  const unsigned int maxLength = calcMaxLength(commands, 4);
  if (is_subcommand) {
    _stream.println("all sub-commands:");
    _stream.print("  help");
    for (unsigned int i = 4; i < maxLength; i++) {
      _stream.print(" ");
    }
    _stream.println("list all sub-commands");
  } else {
    _stream.println("all commands:");
    _stream.print("  help");
    for (unsigned int i = 4; i < maxLength; i++) {
      _stream.print(" ");
    }
    _stream.println("list all commands");
  }
  for (Command const *const command : commands) {
    printCmd(command, maxLength);
  }
}

void HelpPrinter::printArgumentList(const std::list<Argument *> &arguments) {
  const unsigned int maxLength = calcMaxLength(arguments, 0) + 4;
  _stream.println("all arguments:");
  for (Argument const *const argument : arguments) {
    printArg(argument, maxLength);
  }
}

void HelpPrinter::printCmd(Command const *const command, const unsigned int maxLength) {
  _stream.print("  ");
  _stream.print(command->getName());
  for (unsigned int i = command->getName().length(); i < maxLength; i++) {
    _stream.print(" ");
  }
  _stream.println(command->getHelp());
}

void HelpPrinter::printArg(Argument const *const argument, const unsigned int maxLength) {
  _stream.print("  ");
  _stream.print(argument->getName());
  if (argument->getType() == INTEGER) {
    _stream.print(" (INT)");
  } else if (argument->getType() == STRING) {
    _stream.print(" (STR)");
  }
  for (unsigned int i = argument->getName().length() + 6; i < maxLength; i++) {
    _stream.print(" ");
  }
  _stream.println(argument->getHelp());
}
