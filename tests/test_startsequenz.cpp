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

void test_startsequence_initiates() {
    ampel.startSequence();
    TEST_ASSERT_TRUE(ampel.isSequenceRunning());
    TEST_ASSERT_EQUAL(0, ampel.getSequenceStep());
}

void test_startsequence_completes() {
    ampel.startSequence();
    
    // Simulate 6 steps (5 sequence + 1 to complete)
    for (int i = 0; i < 6; i++) {
        delay(SEQ_STEP_DURATION + 10);
        ampel.update();
    }
    
    TEST_ASSERT_FALSE(ampel.isSequenceRunning());
}

void test_reset_stops_sequence() {
    ampel.startSequence();
    TEST_ASSERT_TRUE(ampel.isSequenceRunning());
    
    ampel.reset();
    TEST_ASSERT_FALSE(ampel.isSequenceRunning());
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_startsequence_initiates);
    RUN_TEST(test_startsequence_completes);
    RUN_TEST(test_reset_stops_sequence);
    UNITY_END();
}

void loop() {}
