#include <Arduino.h>
#include <unity.h>
#include "ampel_controller.h"

AmpelController ampel;

void setUp(void) {
    ampel.begin();
}

void tearDown(void) {
    ampel.reset();
}

void test_chaos_red_leds_blink() {
    ampel.setBlinkMode(BlinkMode::RED_ALL);
    TEST_ASSERT_EQUAL(BlinkMode::RED_ALL, ampel.getBlinkMode());
}

void test_chaos_multiple_blinks() {
    ampel.setBlinkMode(BlinkMode::RED_ALL);
    
    // Simulate multiple cycles to check consistent blinking
    for (int cycle = 0; cycle < 3; cycle++) {
        for (int i = 0; i < 10; i++) {
            delay(BLINK_INTERVAL / 5);
            ampel.update();
        }
    }
    
    TEST_ASSERT_EQUAL(BlinkMode::RED_ALL, ampel.getBlinkMode());
}

void test_chaos_clear() {
    ampel.setBlinkMode(BlinkMode::RED_ALL);
    ampel.reset();
    TEST_ASSERT_EQUAL(BlinkMode::OFF, ampel.getBlinkMode());
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_chaos_red_leds_blink);
    RUN_TEST(test_chaos_multiple_blinks);
    RUN_TEST(test_chaos_clear);
    UNITY_END();
}

void loop() {}
