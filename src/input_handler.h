#pragma once
#include <Arduino.h>
#include "config.h"

// Debounce delay in milliseconds
#define DEBOUNCE_DELAY 30

class InputHandler {
public:
    void begin();
    void update();
    bool isStartPressed();
    bool isStopPressed();
    bool isResetPressed();
    bool isModePressed();
    bool isFalseStartDetected();
    
private:
    // Debounce tracking
    struct ButtonState {
        uint8_t pin;
        uint32_t lastDebounceTime;
        bool lastState;
        bool currentState;
        bool pressed;
    };
    
    ButtonState buttons[5] = {
        {BUTTON_START, 0, HIGH, HIGH, false},
        {BUTTON_STOP, 0, HIGH, HIGH, false},
        {BUTTON_RESET, 0, HIGH, HIGH, false},
        {BUTTON_MODE, 0, HIGH, HIGH, false},
        {IR_SCHRANKE, 0, HIGH, HIGH, false}
    };
    
    bool debounce(ButtonState& btn);
    ButtonState& getButtonState(uint8_t pin);
};
