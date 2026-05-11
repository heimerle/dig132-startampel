#include <Arduino.h>
#include <unity.h>
#include "state_machine.h"

void test_state_transitions() {
    // Platzhalter: Test für Zustandswechsel
    TEST_ASSERT_TRUE(true);
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_state_transitions);
    UNITY_END();
}

void loop() {}
