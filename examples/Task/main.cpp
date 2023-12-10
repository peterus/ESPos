#include <Arduino.h>

#include "Task.h"

#ifndef ESPTUX
class Worker : public LoopingTask {
public:
  Worker(unsigned int cnt) : LoopingTask("MyThread", 2), _cnt(cnt) {
  }

private:
  void setup() override {
    Serial.printf("[%d] setup called!\n", _cnt);
  }

  virtual void loop() override {
    Serial.printf("[%d] loop called!\n", _cnt);
    Serial.printf("[%d] %s\n", _cnt, pcTaskGetName(NULL));
    Serial.println(xPortGetCoreID());
  }

  unsigned int _cnt;
};

Worker w1(1);
Worker w2(2);
Worker w3(3);
#endif

void setup() {
  Serial.begin(115200);
  delay(500);

#ifndef ESPTUX
  w1.start();
  w2.start();
  w3.start();
#endif
}

void loop() {
#ifndef ESPTUX
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println("just looping");
  Serial.printf("[%d] %s\n", 6, pcTaskGetName(NULL));
  Serial.println(xPortGetCoreID());
#endif
}
