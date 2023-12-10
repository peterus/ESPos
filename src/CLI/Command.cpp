#include <algorithm>

#include "CLI.h"
#include "Command.h"
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

      auto found = std::find_if(_arguments.begin(), _arguments.end(), [&argument_iter](Argument const *const arg) {
        return *argument_iter == arg->getName();
      });
      if (found != _arguments.end()) {
        argument_iter++;
        (*found)->parse(stream, *argument_iter);
        argument_found = true;
      }

      if (!argument_found) {
        stream.print("argument not found: ");
        stream.print(*argument_iter);
        stream.println();
        stream.println("use 'help' to list all commands");
        return;
      }
    } else {
      auto found = std::find_if(_subCommands.begin(), _subCommands.end(), [&argument_iter](Command const *const subcommand) {
        return *argument_iter == subcommand->getName();
      });
      if (found != _subCommands.end()) {
        argument_iter++;
        std::deque<String> new_args(argument_iter, arguments.end());
        std::copy(_arguments.begin(), _arguments.end(), std::back_inserter(parsedArguments));
        (*found)->parse(stream, new_args, parsedArguments);
        return;
      }

      stream.print("command not found: ");
      stream.print(*argument_iter);
      stream.println();
      stream.println("use 'help' to list all commands");
      return;
    }
  }

  std::copy(_arguments.begin(), _arguments.end(), std::back_inserter(parsedArguments));
  run(parsedArguments);
}
