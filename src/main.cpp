#include <Arduino.h>

unsigned long timer = 0;

void setup() {
    pinMode(13, OUTPUT);
}

void loop() {

    if (millis() - timer > 500) {
        digitalWrite(13, HIGH);
    }

    if (millis() - timer > 1000) {
        digitalWrite(13, LOW);
        timer = millis();
    }

    // Schutz gegen Overflow (optional aber sauber)
    if (timer > millis()) {
        timer = 0;
    }
}
