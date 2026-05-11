#include "state_machine.h"

void StateMachine::begin() {
    input.begin();
    leds.begin();
    currentState = AmpelState::IDLE;
}

void StateMachine::update() {
    // Platzhalter für Haupt-Logik
}

void StateMachine::reset() {
    currentState = AmpelState::IDLE;
    // LEDs ausschalten etc.
}

void StateMachine::setState(AmpelState state) {
    currentState = state;
}

AmpelState StateMachine::getState() const {
    return currentState;
}
