#include "led_controller.h"

void LedController::begin() {
    pinMode(LED1_RED, OUTPUT);
    pinMode(LED1_YELLOW, OUTPUT);
    pinMode(LED1_GREEN, OUTPUT);
    pinMode(LED2_RED, OUTPUT);
    pinMode(LED2_YELLOW, OUTPUT);
    pinMode(LED2_GREEN, OUTPUT);
    // ... ggf. weitere Pins
}

void LedController::setRed(uint8_t lane, bool on) {
    digitalWrite(lane == 1 ? LED1_RED : LED2_RED, on ? HIGH : LOW);
}
void LedController::setYellow(uint8_t lane, bool on) {
    digitalWrite(lane == 1 ? LED1_YELLOW : LED2_YELLOW, on ? HIGH : LOW);
}
void LedController::setGreen(uint8_t lane, bool on) {
    digitalWrite(lane == 1 ? LED1_GREEN : LED2_GREEN, on ? HIGH : LOW);
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
