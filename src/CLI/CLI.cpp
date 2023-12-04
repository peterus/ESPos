#include "CLI.h"

CLI::CLI(const String &appName, const char promt) : _appName(appName), _promt(promt) {
}

void CLI::addCommand(Command *const command) {
  _commands.push_back(command);
}

void CLI::start() {
}
