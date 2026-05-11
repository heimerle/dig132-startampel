#pragma once
#include "input_handler.h"
#include "led_controller.h"

enum class AmpelState {
    IDLE,
    STARTSEQUENCE,
    STARTFREIGABE,
    FRUEHSTART,
    SAFETYCAR,
    CHAOS,
    ENDE
};

class StateMachine {
public:
    void begin();
    void update();
    void reset();
    void setState(AmpelState state);
    AmpelState getState() const;
private:
    AmpelState currentState = AmpelState::IDLE;
    InputHandler input;
    LedController leds;
    // ... weitere interne Variablen
};
