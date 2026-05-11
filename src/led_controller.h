#pragma once
#include <Arduino.h>
#include "config.h"

class LedController {
public:
    void begin();
    void setRed(uint8_t lane, bool on);
    void setYellow(uint8_t lane, bool on);
    void setGreen(uint8_t lane, bool on);
    void blinkRed(uint8_t lane);
    void blinkYellowAll();
    void blinkGreenAll();
    // ... weitere Methoden
};
