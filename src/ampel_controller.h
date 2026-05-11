#pragma once
#include <Arduino.h>
#include "led_controller.h"

// Timing constants (milliseconds)
#define SEQ_STEP_DURATION 500    // Duration of each LED in sequence
#define BLINK_INTERVAL 250       // Blink interval for flashing LEDs

enum class BlinkMode {
    OFF,
    RED_SINGLE,      // Single red LED blinking
    RED_ALL,         // All red LEDs blinking
    YELLOW_ALL,      // All yellow LEDs blinking
    GREEN_ALL        // All green LEDs blinking
};

class AmpelController {
public:
    AmpelController();
    void begin();
    void update();
    
    // Start sequence control
    void startSequence();
    void startFreigabe();
    void reset();
    
    // False start handling
    void setFalseStart(uint8_t lane);
    void clearFalseStart();
    
    // Blink modes
    void setBlinkMode(BlinkMode mode, uint8_t param = 0);
    BlinkMode getBlinkMode() const;
    
    // Winner display
    void setWinnerRed(uint8_t lane);
    
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
    BlinkMode currentBlinkMode = BlinkMode::OFF;
    uint8_t blinkParam = 0;  // Lane number for single LED blink
    
    // False start state
    uint8_t falseStartLane = 0;
    
    // Internal methods
    void updateSequence();
    void updateBlinks();
    void handleBlinkMode();
};
