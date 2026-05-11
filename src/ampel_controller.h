#pragma once
#include <Arduino.h>
#include "led_controller.h"

// Timing constants (milliseconds)
#define SEQ_STEP_DURATION 500    // Duration of each LED in sequence
#define BLINK_INTERVAL 250       // Blink interval for flashing LEDs

class AmpelController {
public:
    AmpelController();
    void begin();
    void update();
    
    // Start sequence control
    void startSequence();
    void startFreigabe();
    void reset();
    
    // Helper methods
    bool isSequenceRunning();
    uint8_t getSequenceStep();
    
private:
    LedController leds;
    
    // Sequence state
    bool sequenceRunning = false;
    uint8_t sequenceStep = 0;
    uint32_t lastStepTime = 0;
    
    // Blink state
    uint32_t lastBlinkTime = 0;
    bool blinkState = false;
    
    // Internal methods
    void updateSequence();
    void updateBlinks();
};
