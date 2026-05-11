#include "input_handler.h"

void InputHandler::begin() {
    pinMode(BUTTON_START, INPUT_PULLUP);
    pinMode(IR_SCHRANKE, INPUT_PULLUP);
    // ... weitere Pins
}

void InputHandler::update() {
    // Hier Entprell-Logik für alle Eingänge
}

bool InputHandler::isStartPressed() {
    // Debounce-Logik für Start-Taster
    return debounce(BUTTON_START);
}

bool InputHandler::isFalseStartDetected() {
    // Debounce-Logik für IR-Schranke
    return debounce(IR_SCHRANKE);
}

bool InputHandler::debounce(uint8_t pin) {
    // Einfache Entprellung (Platzhalter)
    static uint32_t lastPress[16] = {0};
    static bool lastState[16] = {false};
    bool reading = digitalRead(pin) == LOW;
    if (reading != lastState[pin]) {
        lastPress[pin] = millis();
    }
    if ((millis() - lastPress[pin]) > 30) {
        lastState[pin] = reading;
        if (reading) return true;
    }
    return false;
}
