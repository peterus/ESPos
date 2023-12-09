#include <Arduino.h>

#include <CLI/CLI.h>

class WifiCommand : public Command {
public:
  WifiCommand() : Command("wifi", "command for wifi activity") {
  }

  void run(std::list<Argument *> parsedArguments) override {
    Serial.println("wifi run");

    for (auto arg : parsedArguments) {
      Serial.print(arg->getName());
      Serial.print(" ");
      Serial.println(arg->getAsString());
    }
  }
};

class TestArgument : public StringArgument {
public:
  TestArgument() : StringArgument("test", "test argument STR") {
  }
};

class Test1Argument : public IntegerArgument {
public:
  Test1Argument() : IntegerArgument("test1", "test argument INT") {
  }
};

class WifiStartCommand : public Command {
public:
  WifiStartCommand() : Command("start", "start wifi") {
  }

  void run(std::list<Argument *> parsedArguments) override {
    Serial.println("wifi start run");

    for (auto arg : parsedArguments) {
      Serial.print(arg->getName());
      Serial.print(" ");
      Serial.println(arg->getAsString());
    }
  }
};

CLI           _cli(Serial, "TestApp");
WifiCommand   _wifi_cmd;
TestArgument  _wifi_arg;
Test1Argument _wifi_arg1;

WifiStartCommand _wifi_start_cmd;

void setup() {
  Serial.begin(115200);

  _wifi_cmd.addArgument(&_wifi_arg);
  _wifi_cmd.addArgument(&_wifi_arg1);
  _wifi_cmd.addSubcommand(&_wifi_start_cmd);
  _cli.addCommand(&_wifi_cmd);

  _cli.start();
}

void loop() {
  _cli.loop();
}
