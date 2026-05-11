#include <Arduino.h>
#include "state_machine.h"

StateMachine ampel;

void setup() {
    Serial.begin(115200);
    delay(100);
    Serial.println("\n\nStartampel für Carrera-Bahn");
    Serial.println("Initializing...");
    
    ampel.begin();
    
    Serial.println("System ready! Press START button or send GPIO signal to begin.");
}

void loop() {
    ampel.update();
    delay(10);  // Main loop delay
}
