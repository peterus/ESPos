#include "Command.h"
#include "CLI.h"
#include "HelpPrinter.h"

Command::Command(const String &name, const String &help) : _name(name), _help(help) {
}

Command::~Command() {
}

void Command::addSubcommand(Command *const command) {
  _subCommands.push_back(command);
}

void Command::addArgument(Argument *const argument) {
  _arguments.push_back(argument);
}

String Command::getName() const {
  return _name;
}

String Command::getHelp() const {
  return _help;
}

void Command::parse(Stream &stream, std::deque<String> &arguments, std::list<Argument *> parsedArguments) {
  for (auto arg : _arguments) {
    arg->reset();
  }

  if (arguments.size() > 0 && arguments[0] == "help") {
    HelpPrinter helper(stream);
    helper.printCommandList(_subCommands);

    if (_arguments.size() > 0) {
      helper.printArgumentList(_arguments);
    }
    return;
  }

  for (auto argument_iter = arguments.begin(); argument_iter != arguments.end(); argument_iter++) {
    if (argument_iter->startsWith("--")) {
      bool argument_found = false;
      for (auto arg : _arguments) {
        if (*argument_iter == arg->getName()) {
          argument_iter++;
          arg->parse(stream, *argument_iter);
          argument_found = true;
          break;
        }
      }
      if (!argument_found) {
        stream.print("argument not found: ");
        stream.print(*argument_iter);
        stream.println();
        stream.println("use 'help' to list all commands");
        return;
      }
    } else {
      for (auto subcommand : _subCommands) {
        if (*argument_iter == subcommand->getName()) {
          argument_iter++;
          std::deque<String> new_args(argument_iter, arguments.end());
          for (auto arg : _arguments) {
            parsedArguments.push_back(arg);
          }
          subcommand->parse(stream, new_args, parsedArguments);
          return;
        }
      }

      stream.print("command not found: ");
      stream.print(*argument_iter);
      stream.println();
      stream.println("use 'help' to list all commands");
      return;
    }
  }

  for (auto arg : _arguments) {
    parsedArguments.push_back(arg);
  }
  run(parsedArguments);
}
