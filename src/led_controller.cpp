#include "led_controller.h"

void LedController::begin() {
    pinMode(LED1_RED, OUTPUT);
    pinMode(LED1_YELLOW, OUTPUT);
    pinMode(LED1_GREEN, OUTPUT);
    pinMode(LED2_RED, OUTPUT);
    pinMode(LED2_YELLOW, OUTPUT);
    pinMode(LED2_GREEN, OUTPUT);
    // Set all to LOW (off)
    allOff();
}

uint8_t LedController::getPin(uint8_t lane, uint8_t color) {
    // color: 0=RED, 1=YELLOW, 2=GREEN
    if (lane == 1) {
        if (color == 0) return LED1_RED;
        if (color == 1) return LED1_YELLOW;
        if (color == 2) return LED1_GREEN;
    } else if (lane == 2) {
        if (color == 0) return LED2_RED;
        if (color == 1) return LED2_YELLOW;
        if (color == 2) return LED2_GREEN;
    }
    return 0xFF;  // Invalid
}

void LedController::setRed(uint8_t lane, bool on) {
    uint8_t pin = (lane == 1) ? LED1_RED : LED2_RED;
    digitalWrite(pin, on ? HIGH : LOW);
}

void LedController::setYellow(uint8_t lane, bool on) {
    uint8_t pin = (lane == 1) ? LED1_YELLOW : LED2_YELLOW;
    digitalWrite(pin, on ? HIGH : LOW);
}

void LedController::setGreen(uint8_t lane, bool on) {
    uint8_t pin = (lane == 1) ? LED1_GREEN : LED2_GREEN;
    digitalWrite(pin, on ? HIGH : LOW);
}

void LedController::setAllRed(bool on) {
    for (uint8_t lane = 1; lane <= NUM_LANES; lane++) {
        setRed(lane, on);
    }
}

void LedController::setAllYellow(bool on) {
    for (uint8_t lane = 1; lane <= NUM_LANES; lane++) {
        setYellow(lane, on);
    }
}

void LedController::setAllGreen(bool on) {
    for (uint8_t lane = 1; lane <= NUM_LANES; lane++) {
        setGreen(lane, on);
    }
}

void LedController::allOff() {
    setAllRed(false);
    setAllYellow(false);
    setAllGreen(false);
}

void LedController::blinkRed(uint8_t lane) {
    // Platzhalter für Blinklogik
}

void LedController::blinkYellowAll() {
    // Platzhalter für synchrones Blinken
}

void LedController::blinkGreenAll() {
    // Platzhalter für synchrones Blinken
}
