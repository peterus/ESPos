#include "CLI.h"
#include "HelpPrinter.h"

CLI::CLI(Stream &stream, const String &appName, bool echo, const char prompt) : _stream(stream), _appName(appName), _prompt(prompt), _echo(echo) {
}

void CLI::addCommand(Command *const command) {
  _commands.push_back(command);
}

void CLI::start() {
  _stream.println("Starting CLI...");
  printPrompt();
}

void CLI::loop() {
  if (_stream.available()) {
    processStream();
  }
}

void CLI::printPrompt() {
  _stream.write(_prompt);
  _stream.write(" ");
}

void CLI::processStream() {
  char c = _stream.read();

  // execute with 'new line'
  if (c == '\n') {
    _stream.write("\n\r");
    _commandLine.trim();
    if (_commandLine.length() > 0) {
      auto splitted = getStringSplitted(_commandLine);
      parse(_stream, splitted);
      _commandLine = "";
    }
    printPrompt();
  }
  // remove last character on on backspace
  else if (c == '\b' || c == 127) {
    if (_commandLine.length() > 0) {
      _commandLine.remove(_commandLine.length() - 1);
      if (_echo) {
        _stream.write("\b \b");
      }
    }
  }
  // add character to line
  else {
    _commandLine += c;
    if (_echo) {
      _stream.write(c);
    }
  }
}

void CLI::parse(Stream &stream, std::deque<String> &arguments) {
  const String cmd = arguments[0];

  if (cmd == "help") {
    HelpPrinter helper(_stream);
    helper.printCommandList(_commands, false);
    return;
  }

  auto found = std::find_if(_commands.begin(), _commands.end(), [&cmd](Command const *const command) {
    return command->getName() == cmd;
  });
  if (found != _commands.end()) {
    arguments.pop_front();
    std::list<Argument *> parsedArguments;
    (*found)->parse(stream, arguments, parsedArguments);
    return;
  }

  _stream.print("command not found: ");
  _stream.print(cmd);
  _stream.println();
  _stream.println("use 'help' to list all commands");
}

std::deque<String> getStringSplitted(String line) {
  std::deque<String> splitted;

  int start_index = 0;
  int end_index   = line.indexOf(' ');
  do {
    end_index = line.indexOf(' ', start_index);

    String split = line.substring(start_index, end_index);
    split.trim();
    splitted.push_back(split);

    start_index = end_index + 1;
  } while (end_index != -1);

  return splitted;
}
