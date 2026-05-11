#include "ampel_controller.h"

AmpelController::AmpelController() {
    // Constructor
}

void AmpelController::begin() {
    leds.begin();
}

void AmpelController::update() {
    if (sequenceRunning) {
        updateSequence();
    }
    if (currentBlinkMode != BlinkMode::OFF) {
        updateBlinks();
    }
}

void AmpelController::startSequence() {
    sequenceRunning = true;
    sequenceStep = 0;
    lastStepTime = millis();
    currentBlinkMode = BlinkMode::OFF;
    
    // Turn off all LEDs before starting
    leds.allOff();
}

void AmpelController::startFreigabe() {
    sequenceRunning = false;
    currentBlinkMode = BlinkMode::OFF;
    
    // Turn off all red and yellow LEDs, turn on green
    for (uint8_t lane = 1; lane <= NUM_LANES; lane++) {
        leds.setRed(lane, false);
        leds.setYellow(lane, false);
        leds.setGreen(lane, true);
    }
}

void AmpelController::reset() {
    sequenceRunning = false;
    sequenceStep = 0;
    lastStepTime = 0;
    blinkState = false;
    currentBlinkMode = BlinkMode::OFF;
    falseStartLane = 0;
    
    // Turn off all LEDs
    leds.allOff();
}

void AmpelController::setFalseStart(uint8_t lane) {
    falseStartLane = lane;
    setBlinkMode(BlinkMode::RED_SINGLE, lane);
    leds.setAllYellow(true);  // Turn on all yellow LEDs
}

void AmpelController::clearFalseStart() {
    falseStartLane = 0;
    setBlinkMode(BlinkMode::OFF);
}

void AmpelController::setBlinkMode(BlinkMode mode, uint8_t param) {
    currentBlinkMode = mode;
    blinkParam = param;
    lastBlinkTime = millis();
    blinkState = false;
}

BlinkMode AmpelController::getBlinkMode() const {
    return currentBlinkMode;
}

bool AmpelController::isSequenceRunning() {
    return sequenceRunning;
}

uint8_t AmpelController::getSequenceStep() {
    return sequenceStep;
}

void AmpelController::updateSequence() {
    uint32_t currentTime = millis();
    
    // Each step (0-4 represents the 5 red LEDs)
    if (currentTime - lastStepTime >= SEQ_STEP_DURATION) {
        if (sequenceStep < 5) {
            // Turn on the next red LED for this step
            for (uint8_t lane = 1; lane <= NUM_LANES; lane++) {
                leds.setRed(lane, true);
            }
            sequenceStep++;
            lastStepTime = currentTime;
        } else {
            // Sequence complete, transition to green
            startFreigabe();
        }
    }
}

void AmpelController::updateBlinks() {
    handleBlinkMode();
}

void AmpelController::handleBlinkMode() {
    uint32_t currentTime = millis();
    
    if (currentTime - lastBlinkTime >= BLINK_INTERVAL) {
        blinkState = !blinkState;
        lastBlinkTime = currentTime;
        
        switch (currentBlinkMode) {
            case BlinkMode::RED_SINGLE:
                if (falseStartLane > 0) {
                    leds.setRed(falseStartLane, blinkState);
                }
                break;
            case BlinkMode::RED_ALL:
                leds.setAllRed(blinkState);
                break;
            case BlinkMode::YELLOW_ALL:
                leds.setAllYellow(blinkState);
                break;
            case BlinkMode::GREEN_ALL:
                leds.setAllGreen(blinkState);
                break;
            case BlinkMode::OFF:
            default:
                break;
        }
    }
}
