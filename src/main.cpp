#include <Arduino.h>
#include "pins.h"
#include "secret.h"
#include "logger.h"

unsigned long timer = 0;

void setup() {
    Serial.begin(115200);
    delay(500);

    pinMode(LED_PIN, OUTPUT);

    log(INFO, "System gestartet");
    log(INFO, "WLAN SSID", WIFI_SSID);
}

void loop() {

    unsigned long currentMillis = millis();

    // ===== Overflow-Schutz (optional) =====
    if (currentMillis < timer) {
        log(WARN, "millis Overflow erkannt");
        timer = 0;
    }

    // ===== LED EIN nach 500 ms =====
    if (currentMillis - timer > 500) {
        digitalWrite(LED_PIN, HIGH);
    }

    // ===== LED AUS nach 1000 ms =====
    if (currentMillis - timer > 1000) {

        digitalWrite(LED_PIN, LOW);

        log(SUCCESS, "LED AUS bei millis", currentMillis);

        timer = currentMillis;
    }
}
