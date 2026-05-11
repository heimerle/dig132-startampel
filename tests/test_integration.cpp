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

void test_full_sequence_flow() {
    // Test complete flow: IDLE -> STARTSEQUENCE -> STARTFREIGABE
    TEST_ASSERT_EQUAL(AmpelState::IDLE, ampel.getState());
    
    ampel.handleStartEvent();
    TEST_ASSERT_EQUAL(AmpelState::STARTSEQUENCE, ampel.getState());
    
    // Simulate sequence completion
    for (int i = 0; i < 6; i++) {
        delay(SEQ_STEP_DURATION + 10);
        ampel.update();
    }
    
    TEST_ASSERT_EQUAL(AmpelState::STARTFREIGABE, ampel.getState());
}

void test_reset_from_sequence() {
    ampel.handleStartEvent();
    TEST_ASSERT_EQUAL(AmpelState::STARTSEQUENCE, ampel.getState());
    
    ampel.handleResetEvent();
    TEST_ASSERT_EQUAL(AmpelState::IDLE, ampel.getState());
}

void test_false_start_from_sequence() {
    ampel.handleStartEvent();
    ampel.handleFalseStartEvent();
    TEST_ASSERT_EQUAL(AmpelState::FRUEHSTART, ampel.getState());
}

void test_safety_car_from_freigabe() {
    ampel.handleStartEvent();
    // Simulate sequence completion
    for (int i = 0; i < 6; i++) {
        delay(SEQ_STEP_DURATION + 10);
        ampel.update();
    }
    
    ampel.handleSafetyCarEvent();
    TEST_ASSERT_EQUAL(AmpelState::SAFETYCAR, ampel.getState());
}

void test_chaos_from_freigabe() {
    ampel.handleStartEvent();
    for (int i = 0; i < 6; i++) {
        delay(SEQ_STEP_DURATION + 10);
        ampel.update();
    }
    
    ampel.handleChaosEvent();
    TEST_ASSERT_EQUAL(AmpelState::CHAOS, ampel.getState());
}

void test_rennende_from_freigabe() {
    ampel.handleStartEvent();
    for (int i = 0; i < 6; i++) {
        delay(SEQ_STEP_DURATION + 10);
        ampel.update();
    }
    
    ampel.handleEndEvent(1);
    TEST_ASSERT_EQUAL(AmpelState::ENDE, ampel.getState());
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_full_sequence_flow);
    RUN_TEST(test_reset_from_sequence);
    RUN_TEST(test_false_start_from_sequence);
    RUN_TEST(test_safety_car_from_freigabe);
    RUN_TEST(test_chaos_from_freigabe);
    RUN_TEST(test_rennende_from_freigabe);
    UNITY_END();
}

void loop() {}
