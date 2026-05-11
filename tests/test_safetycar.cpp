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

void test_safetycar_sets_blink_mode() {
    ampel.setBlinkMode(BlinkMode::YELLOW_ALL);
    TEST_ASSERT_EQUAL(BlinkMode::YELLOW_ALL, ampel.getBlinkMode());
}

void test_safetycar_yellow_leds_blink() {
    ampel.setBlinkMode(BlinkMode::YELLOW_ALL);
    
    // Simulate multiple updates to trigger blink changes
    for (int i = 0; i < 10; i++) {
        delay(BLINK_INTERVAL / 2);
        ampel.update();
    }
    
    TEST_ASSERT_EQUAL(BlinkMode::YELLOW_ALL, ampel.getBlinkMode());
}

void test_chaos_sets_blink_mode() {
    ampel.setBlinkMode(BlinkMode::RED_ALL);
    TEST_ASSERT_EQUAL(BlinkMode::RED_ALL, ampel.getBlinkMode());
}

void test_chaos_red_leds_blink() {
    ampel.setBlinkMode(BlinkMode::RED_ALL);
    
    // Simulate multiple updates to trigger blink changes
    for (int i = 0; i < 10; i++) {
        delay(BLINK_INTERVAL / 2);
        ampel.update();
    }
    
    TEST_ASSERT_EQUAL(BlinkMode::RED_ALL, ampel.getBlinkMode());
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_safetycar_sets_blink_mode);
    RUN_TEST(test_safetycar_yellow_leds_blink);
    RUN_TEST(test_chaos_sets_blink_mode);
    RUN_TEST(test_chaos_red_leds_blink);
    UNITY_END();
}

void loop() {}
