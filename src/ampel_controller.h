#pragma once
#include <Arduino.h>
#include "led_controller.h"

// Timing constants (milliseconds)
#define SEQ_STEP_DURATION 500    // Duration of each LED in sequence
#define BLINK_INTERVAL 250       // Blink interval for flashing LEDs

/**
 * Blink modes for LED patterns
 */
enum class BlinkMode {
    OFF,
    RED_SINGLE,      // Single red LED blinking (for false start detection)
    RED_ALL,         // All red LEDs blinking (chaos/interruption)
    YELLOW_ALL,      // All yellow LEDs blinking (safety-car mode)
    GREEN_ALL        // All green LEDs blinking (race end)
};

/**
 * AmpelController: Central LED sequence and blink management
 * 
 * Responsible for:
 * - Managing start sequences (5-step countdown with red LEDs)
 * - Controlling blink patterns for different race states
 * - Transitioning between start sequence and race start signal
 * - Handling false start LED patterns
 */
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
