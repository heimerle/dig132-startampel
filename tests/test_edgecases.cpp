#include <Arduino.h>
#include <unity.h>
#include "state_machine.h"

StateMachine ampel;

void setUp(void) {
    ampel.begin();
}

void tearDown(void) {
    ampel.reset();
}

void test_reset_during_blink_mode() {
    ampel.handleStartEvent();
    
    // Transition to safety car (blinking mode)
    for (int i = 0; i < 6; i++) {
        delay(SEQ_STEP_DURATION + 10);
        ampel.update();
    }
    ampel.handleSafetyCarEvent();
    TEST_ASSERT_EQUAL(AmpelState::SAFETYCAR, ampel.getState());
    
    // Reset during blink mode
    ampel.handleResetEvent();
    TEST_ASSERT_EQUAL(AmpelState::IDLE, ampel.getState());
}

void test_multiple_reset_calls() {
    ampel.handleStartEvent();
    ampel.handleResetEvent();
    TEST_ASSERT_EQUAL(AmpelState::IDLE, ampel.getState());
    
    // Multiple reset calls should not cause issues
    ampel.handleResetEvent();
    ampel.handleResetEvent();
    TEST_ASSERT_EQUAL(AmpelState::IDLE, ampel.getState());
}

void test_start_from_false_start_state() {
    ampel.handleStartEvent();
    ampel.handleFalseStartEvent();
    TEST_ASSERT_EQUAL(AmpelState::FRUEHSTART, ampel.getState());
    
    // Reset and start again
    ampel.handleResetEvent();
    ampel.handleStartEvent();
    TEST_ASSERT_EQUAL(AmpelState::STARTSEQUENCE, ampel.getState());
}

void test_false_start_not_triggered_outside_sequence() {
    // False start should not trigger in IDLE state
    ampel.handleFalseStartEvent();
    TEST_ASSERT_EQUAL(AmpelState::IDLE, ampel.getState());
}

void test_safety_car_priority_over_false_start() {
    ampel.handleStartEvent();
    
    // Transition to freigabe
    for (int i = 0; i < 6; i++) {
        delay(SEQ_STEP_DURATION + 10);
        ampel.update();
    }
    
    ampel.handleSafetyCarEvent();
    TEST_ASSERT_EQUAL(AmpelState::SAFETYCAR, ampel.getState());
    
    // False start should not affect SAFETYCAR state
    ampel.handleFalseStartEvent();
    TEST_ASSERT_EQUAL(AmpelState::SAFETYCAR, ampel.getState());
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_reset_during_blink_mode);
    RUN_TEST(test_multiple_reset_calls);
    RUN_TEST(test_start_from_false_start_state);
    RUN_TEST(test_false_start_not_triggered_outside_sequence);
    RUN_TEST(test_safety_car_priority_over_false_start);
    UNITY_END();
}

void loop() {}
