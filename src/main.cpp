// ============================================================
// MAIN PROGRAM
// startet System und führt Hauptloop aus
// ============================================================

#include <Arduino.h>

#include "pins.h"
#include "secret.h"

#include "../src/Debug/logger.h"

#include "../src/ESP32/config/device_config.h"
#include "../src/ESP32/wifi/wifi_manager.h"
#include "../src/ESP32/time/uhr.h"
#include "../src/ESP32/web/router.h"

// speichert Zeit für LED Zyklus
unsigned long timer = 0;

// Beispiel Event Zeit in millis
unsigned long demoEventMillis = 0;

void setup()
{
    // startet serielle Ausgabe
    Serial.begin(115200);
    delay(500);

    // setzt LED Pin als Ausgang
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    log(INFO, "System gestartet");
    log(INFO, "Device ID", DEVICE_ID);
    log(INFO, "SSID", WIFI_SSID);

    // verbindet WLAN
    initWifi();

    // synchronisiert Zeit und speichert Zeitanker
    initClock();

    // startet Webserver
    initRouter();

    // speichert einmal einen Demo Zeitpunkt in millis
    demoEventMillis = millis();

    // zeigt dazu die echte Uhrzeit
    log(INFO, "Demo Event millis", demoEventMillis);
    log(INFO, "Demo Event Zeit", millisToTimeString(demoEventMillis));
}

void loop()
{
    // verarbeitet HTTP Anfragen
    updateRouter();

    // prüft WLAN Verbindung
    updateWifi();

    unsigned long currentMillis = millis();

    // erkennt millis overflow
    if (currentMillis < timer)
    {
        log(WARN, "millis overflow");
        timer = 0;
    }

    // LED einschalten
    if (currentMillis - timer > LED_ON_TIME_MS)
    {
        digitalWrite(LED_PIN, HIGH);
    }

    // LED ausschalten
    if (currentMillis - timer > LED_OFF_TIME_MS)
    {
        digitalWrite(LED_PIN, LOW);

        log(SUCCESS, "SUCCESS", currentMillis);
        log(INFO, "INFO", 1);
        log(WARN, "WARN", 1);
        log(ERROR, "ERROR", 1);
        log(DEBUG, "DEBUG", 1);

        // Beispiel: aktuelle millis Zeit in echte Uhrzeit umrechnen
        log(INFO, "Jetzt als Zeit", millisToTimeString(currentMillis));

        timer = currentMillis;
    }
}