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
    updateBlinks();
}

void AmpelController::startSequence() {
    sequenceRunning = true;
    sequenceStep = 0;
    lastStepTime = millis();
    
    // Turn off all LEDs before starting
    for (uint8_t lane = 1; lane <= NUM_LANES; lane++) {
        leds.setRed(lane, false);
        leds.setYellow(lane, false);
        leds.setGreen(lane, false);
    }
}

void AmpelController::startFreigabe() {
    sequenceRunning = false;
    
    // Turn off all red and yellow LEDs
    for (uint8_t lane = 1; lane <= NUM_LANES; lane++) {
        leds.setRed(lane, false);
        leds.setYellow(lane, false);
        leds.setGreen(lane, true);  // Turn on green LEDs
    }
}

void AmpelController::reset() {
    sequenceRunning = false;
    sequenceStep = 0;
    lastStepTime = 0;
    blinkState = false;
    
    // Turn off all LEDs
    for (uint8_t lane = 1; lane <= NUM_LANES; lane++) {
        leds.setRed(lane, false);
        leds.setYellow(lane, false);
        leds.setGreen(lane, false);
    }
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
            sequenceRunning = false;
            startFreigabe();
        }
    }
}

void AmpelController::updateBlinks() {
    // Placeholder for blink update logic
    // This will be used for false start and other blinking modes
}
