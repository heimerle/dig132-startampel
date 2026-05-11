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

void test_rennende_sets_green_blink() {
    ampel.setBlinkMode(BlinkMode::GREEN_ALL);
    TEST_ASSERT_EQUAL(BlinkMode::GREEN_ALL, ampel.getBlinkMode());
}

void test_rennende_winner_red_led() {
    ampel.setBlinkMode(BlinkMode::GREEN_ALL);
    ampel.setWinnerRed(1);
    
    // Check that green blink mode is still active
    TEST_ASSERT_EQUAL(BlinkMode::GREEN_ALL, ampel.getBlinkMode());
}

void test_rennende_green_leds_blink() {
    ampel.setBlinkMode(BlinkMode::GREEN_ALL);
    
    // Simulate multiple updates to trigger blink changes
    for (int i = 0; i < 10; i++) {
        delay(BLINK_INTERVAL / 2);
        ampel.update();
    }
    
    TEST_ASSERT_EQUAL(BlinkMode::GREEN_ALL, ampel.getBlinkMode());
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_rennende_sets_green_blink);
    RUN_TEST(test_rennende_winner_red_led);
    RUN_TEST(test_rennende_green_leds_blink);
    UNITY_END();
}

void loop() {}
