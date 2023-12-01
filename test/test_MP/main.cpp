#include <gtest/gtest.h>

#ifdef ARDUINO
#include <Arduino.h>

void setup() {
  Serial.begin(115200);

  ::testing::InitGoogleTest();
}

void loop() {
  if (RUN_ALL_TESTS())
    ;

  delay(1000);
}

#else
int main(int argc, char **argv) {

  ::testing::InitGoogleTest(&argc, argv);

  if (RUN_ALL_TESTS())
    ;

  return 0;
}
#endif
