#include <Arduino.h>
#include "state_machine.h"

StateMachine ampel;

void setup() {
    ampel.begin();
}

void loop() {
    ampel.update();
    delay(10); // Main loop delay
}
