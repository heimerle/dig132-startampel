#include "input_handler.h"

void InputHandler::begin() {
    pinMode(BUTTON_START, INPUT_PULLUP);
    pinMode(BUTTON_STOP, INPUT_PULLUP);
    pinMode(BUTTON_RESET, INPUT_PULLUP);
    pinMode(BUTTON_MODE, INPUT_PULLUP);
    pinMode(IR_SCHRANKE, INPUT_PULLUP);
    pinMode(GPIO_START, INPUT_PULLUP);
    pinMode(GPIO_FRUEH, INPUT_PULLUP);
}

void InputHandler::update() {
    // Update all buttons
    for (int i = 0; i < 5; i++) {
        debounce(buttons[i]);
    }
}

bool InputHandler::isStartPressed() {
    ButtonState& btn = getButtonState(BUTTON_START);
    bool result = btn.pressed;
    btn.pressed = false;  // Reset after reading
    return result;
}

bool InputHandler::isStopPressed() {
    ButtonState& btn = getButtonState(BUTTON_STOP);
    bool result = btn.pressed;
    btn.pressed = false;
    return result;
}

bool InputHandler::isResetPressed() {
    ButtonState& btn = getButtonState(BUTTON_RESET);
    bool result = btn.pressed;
    btn.pressed = false;
    return result;
}

bool InputHandler::isModePressed() {
    ButtonState& btn = getButtonState(BUTTON_MODE);
    bool result = btn.pressed;
    btn.pressed = false;
    return result;
}

bool InputHandler::isFalseStartDetected() {
    ButtonState& btn = getButtonState(IR_SCHRANKE);
    bool result = btn.pressed;
    btn.pressed = false;
    return result;
}

InputHandler::ButtonState& InputHandler::getButtonState(uint8_t pin) {
    for (int i = 0; i < 5; i++) {
        if (buttons[i].pin == pin) {
            return buttons[i];
        }
    }
    return buttons[0];  // Default fallback
}

bool InputHandler::debounce(ButtonState& btn) {
    bool reading = digitalRead(btn.pin) == LOW;  // LOW = pressed (PULLUP logic)
    
    if (reading != btn.lastState) {
        btn.lastDebounceTime = millis();
        btn.lastState = reading;
    }
    
    if ((millis() - btn.lastDebounceTime) > DEBOUNCE_DELAY) {
        if (reading != btn.currentState) {
            btn.currentState = reading;
            if (reading) {
                btn.pressed = true;  // Button pressed
            }
        }
    }
    
    return btn.pressed;
}
