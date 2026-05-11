#pragma once
#include <Arduino.h>
#include "config.h"

class LedController {
public:
    void begin();
    void setRed(uint8_t lane, bool on);
    void setYellow(uint8_t lane, bool on);
    void setGreen(uint8_t lane, bool on);
    void setAllRed(bool on);
    void setAllYellow(bool on);
    void setAllGreen(bool on);
    void allOff();
    void blinkRed(uint8_t lane);
    void blinkYellowAll();
    void blinkGreenAll();
private:
    uint8_t getPin(uint8_t lane, uint8_t color);
};
