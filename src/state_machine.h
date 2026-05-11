#pragma once
#include "input_handler.h"
#include "ampel_controller.h"

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
    void handleStartEvent();
    void handleFalseStartEvent();
    void handleResetEvent();
    void handleSafetyCarEvent();
    void handleChaosEvent();
    void handleEndEvent(uint8_t winnerLane = 0);
private:
    AmpelState currentState = AmpelState::IDLE;
    InputHandler input;
    AmpelController ampel;
    uint8_t winnerLane = 0;
};

