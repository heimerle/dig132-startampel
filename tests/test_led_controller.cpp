#include <Arduino.h>
#include <unity.h>
#include "led_controller.h"

void test_led_output() {
    // Platzhalter: Test für LED-Ausgänge
    TEST_ASSERT_TRUE(true);
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_led_output);
    UNITY_END();
}

void loop() {}
