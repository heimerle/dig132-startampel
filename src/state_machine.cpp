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
    if (input.isModePressed()) {
        // Can be extended for mode switching or other functionality
    }
}

void StateMachine::reset() {
    currentState = AmpelState::IDLE;
    ampel.reset();
    winnerLane = 0;
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
        ampel.setFalseStart(1);
    }
}

void StateMachine::handleSafetyCarEvent() {
    if (currentState == AmpelState::STARTFREIGABE) {
        currentState = AmpelState::SAFETYCAR;
        ampel.setBlinkMode(BlinkMode::YELLOW_ALL);
    }
}

void StateMachine::handleChaosEvent() {
    if (currentState == AmpelState::STARTFREIGABE) {
        currentState = AmpelState::CHAOS;
        ampel.setBlinkMode(BlinkMode::RED_ALL);
    }
}

void StateMachine::handleEndEvent(uint8_t winnerLane) {
    currentState = AmpelState::ENDE;
    this->winnerLane = winnerLane;
    ampel.setBlinkMode(BlinkMode::GREEN_ALL);
    if (winnerLane > 0) {
        ampel.setWinnerRed(winnerLane);
    }
}
