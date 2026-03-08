// ============================================================
// RELAY IMPLEMENTATION
// erzeugt einen 0.5 Sekunden Puls auf RELAY_PIN
// ============================================================

#include "relay.h"

#include <Arduino.h>

#include "../include/pins.h"
#include "../include/system_state.h"
#include "../src/Debug/logger.h"

// merkt sich ob gerade ein Puls läuft
static bool relayPulseActive = false;

// speichert wann der Puls gestartet wurde
static unsigned long relayPulseStart = 0;

// feste Pulsdauer in Millisekunden
static const unsigned long RELAY_PULSE_MS = 500;

// initialisiert den Relay Ausgang
void initRelay()
{
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);

    relayPulseActive = false;
    relayPulseStart = 0;

    log(INFO, "Relay initialisiert");
}

// verarbeitet Relay Trigger und beendet laufende Pulse
void updateRelay()
{
    unsigned long currentMillis = millis();

    // startet einen neuen Puls wenn ein Trigger gesetzt wurde
    if (relayPulseRequest && !relayPulseActive)
    {
        relayPulseRequest = false;
        relayPulseActive = true;
        relayPulseStart = currentMillis;

        digitalWrite(RELAY_PIN, HIGH);

        log(INFO, "Relay Puls gestartet");
        log(INFO, "Relay Start millis", relayPulseStart);
    }

    // beendet den Puls nach 0.5 Sekunden
    if (relayPulseActive && (currentMillis - relayPulseStart >= RELAY_PULSE_MS))
    {
        digitalWrite(RELAY_PIN, LOW);
        relayPulseActive = false;

        log(INFO, "Relay Puls beendet");
        log(INFO, "Relay Ende millis", currentMillis);
    }
}