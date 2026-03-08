// ============================================================
// ON LIGHT IMPLEMENTATION
// blinkt die Status LED mit den Zeiten aus device_config.h
// ============================================================

#include "on_light.h"

#include <Arduino.h>

#include "../../../include/pins.h"
#include "../../Debug/logger.h"
#include "../config/device_config.h"

// speichert den Startpunkt vom Blinkzyklus
static unsigned long onLightTimer = 0;

// merkt sich ob die LED im aktuellen Zyklus schon eingeschaltet wurde
static bool ledIsOn = false;

// initialisiert die Status LED
void initOnLight()
{
    pinMode(ON_STATUS_PIN, OUTPUT);
    digitalWrite(ON_STATUS_PIN, LOW);

    onLightTimer = millis();
    ledIsOn = false;

    log(INFO, "On Light initialisiert");
}

// verarbeitet den Blinkzyklus
void updateOnLight()
{
    unsigned long currentMillis = millis();

    // erkennt millis overflow und setzt den Zyklus neu
    if (currentMillis < onLightTimer)
    {
        log(WARN, "millis overflow bei On Light");
        onLightTimer = 0;
        ledIsOn = false;
        digitalWrite(ON_STATUS_PIN, LOW);
    }

    // schaltet die LED nach der Einschaltzeit ein
    if (!ledIsOn && (currentMillis - onLightTimer >= LED_ON_TIME_MS))
    {
        digitalWrite(ON_STATUS_PIN, HIGH);
        ledIsOn = true;
    }

    // schaltet die LED nach der Ausschaltzeit wieder aus und startet neu
    if (currentMillis - onLightTimer >= LED_OFF_TIME_MS)
    {
        digitalWrite(ON_STATUS_PIN, LOW);
        ledIsOn = false;
        onLightTimer = currentMillis;
    }
}