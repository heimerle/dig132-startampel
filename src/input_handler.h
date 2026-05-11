#pragma once
#include <Arduino.h>
#include "config.h"

class InputHandler {
public:
    void begin();
    void update();
    bool isStartPressed();
    bool isFalseStartDetected();
    // ... weitere Methoden für Stop, Reset, Mode, etc.
private:
    bool debounce(uint8_t pin);
    // ... interne Zustände
};
