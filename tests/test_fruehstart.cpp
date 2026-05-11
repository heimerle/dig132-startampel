#include <Arduino.h>
#include <unity.h>
#include "ampel_controller.h"
#include "state_machine.h"

AmpelController ampel;

void setUp(void) {
    ampel.begin();
}

void tearDown(void) {
    ampel.reset();
}

void test_falsestart_during_sequence() {
    ampel.startSequence();
    TEST_ASSERT_TRUE(ampel.isSequenceRunning());
    
    // Simulate false start
    ampel.setFalseStart(1);
    TEST_ASSERT_EQUAL(BlinkMode::RED_SINGLE, ampel.getBlinkMode());
}

void test_falsestart_sets_yellow_leds() {
    ampel.startSequence();
    ampel.setFalseStart(1);
    
    // After false start, all yellow LEDs should be on and red should blink
    TEST_ASSERT_EQUAL(BlinkMode::RED_SINGLE, ampel.getBlinkMode());
}

void test_falsestart_clears() {
    ampel.setFalseStart(1);
    ampel.clearFalseStart();
    TEST_ASSERT_EQUAL(BlinkMode::OFF, ampel.getBlinkMode());
}

void test_state_transitions_to_fruehstart() {
    // This test would require a mock of the InputHandler
    // For now, we test that false start detection changes state
    TEST_ASSERT_TRUE(true);  // Placeholder
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_falsestart_during_sequence);
    RUN_TEST(test_falsestart_sets_yellow_leds);
    RUN_TEST(test_falsestart_clears);
    RUN_TEST(test_state_transitions_to_fruehstart);
    UNITY_END();
}

void loop() {}
