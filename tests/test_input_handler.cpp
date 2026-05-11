#include <Arduino.h>
#include <unity.h>
#include "input_handler.h"

void test_start_button() {
    // Platzhalter: Test für Start-Taster
    TEST_ASSERT_TRUE(true);
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_start_button);
    UNITY_END();
}

void loop() {}
