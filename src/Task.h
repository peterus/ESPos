#ifndef TASK_H_
#define TASK_H_

#include <Arduino.h>

constexpr uint32_t STACK_SIZE = 4096;

class TaskBase {
public:
  virtual ~TaskBase();

protected:
  xTaskHandle taskHandle;
};

class Task : public TaskBase {
public:
  Task(const char *name, UBaseType_t priority, const uint32_t stackDepth = STACK_SIZE);

  void start();

private:
  static void taskfun(void *parm);

  virtual void task() = 0;

  const char       *_name;
  const UBaseType_t _priority;
  const uint32_t    _stackDepth;
};

class LoopingTask : public Task {
public:
  LoopingTask(const char *name, UBaseType_t priority, unsigned int waitTime = 100, const uint32_t stackDepth = STACK_SIZE);

private:
  void task() override;

  virtual void setup() = 0;
  virtual void loop()  = 0;

  const unsigned int _waitTime;
};

#endif
