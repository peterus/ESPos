#ifdef ARDUINO
#ifndef ESPTUX

#include "Task.h"

TaskBase::TaskBase() : taskHandle(0) {
}

TaskBase::~TaskBase() {
}

Task::Task(const char *name, UBaseType_t priority, const uint32_t stackDepth) : _name(name), _priority(priority), _stackDepth(stackDepth) {
}

void Task::start() {
  xTaskCreate(&taskfun, _name, _stackDepth, this, _priority, &taskHandle);
}

void Task::taskfun(void *parm) {
  static_cast<Task *>(parm)->task();
}

LoopingTask::LoopingTask(const char *name, UBaseType_t priority, unsigned int waitTime, const uint32_t stackDepth) : Task(name, priority, stackDepth), _waitTime(waitTime) {
}

void LoopingTask::task() {
  setup();
  while (true) {
#ifdef portTICK_RATE_MS
    vTaskDelay(_waitTime / portTICK_RATE_MS);
#else
    vTaskDelay(_waitTime / portTICK_PERIOD_MS);
#endif
    loop();
  }
}

#endif
#endif
