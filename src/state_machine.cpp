#include "state_machine.h"

void StateMachine::begin() {
    input.begin();
    ampel.begin();
    currentState = AmpelState::IDLE;
}

void StateMachine::update() {
    input.update();
    ampel.update();
    
    // Handle input events
    if (input.isStartPressed()) {
        handleStartEvent();
    }
    if (input.isResetPressed()) {
        handleResetEvent();
    }
    if (input.isFalseStartDetected()) {
        handleFalseStartEvent();
    }
}

void StateMachine::reset() {
    currentState = AmpelState::IDLE;
    ampel.reset();
}

void StateMachine::setState(AmpelState state) {
    currentState = state;
}

AmpelState StateMachine::getState() const {
    return currentState;
}

void StateMachine::handleStartEvent() {
    if (currentState == AmpelState::IDLE) {
        currentState = AmpelState::STARTSEQUENCE;
        ampel.startSequence();
    }
}

void StateMachine::handleResetEvent() {
    reset();
}

void StateMachine::handleFalseStartEvent() {
    if (currentState == AmpelState::STARTSEQUENCE) {
        currentState = AmpelState::FRUEHSTART;
        // Simulate false start on Lane 1 (can be extended to detect which lane)
        ampel.setFalseStart(1);
    }
}
