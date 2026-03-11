// ============================================================
// MAIN PROGRAM
// startet das System und ruft alle Module im loop auf
// ============================================================

#include <Arduino.h>

#include "pins.h"
#include "secret.h"
#include "system_state.h"
#include "system_state.h"


#include "../src/Debug/logger.h"

#include "../src/ESP32/config/device_config.h"
#include "../src/ESP32/on_light/on_light.h"
#include "../src/ESP32/time/uhr.h"
#include "../src/ESP32/web/router.h"
#include "../src/ESP32/wifi/wifi_manager.h"
#include "../src/relay/relay.h"
#include "./micro_sd/micro_sd.h"
#include "./ESP32/ota/ota_manager.h"

// speichert ein Demo Event für die Zeitumrechnung
unsigned long demoEventMillis = 0;

void setup()
{
    // startet die serielle Ausgabe
    Serial.begin(115200);
    delay(500);

    // startet die blinkende Status LED
    initOnLight();

    // startet den Relay Ausgang
    initRelay();

    // startet die micro SD Karte
    initMicroSD();

    // Test: Datei neu schreiben
    writeTextFile("/test.txt", "Hallo von der micro SD\n");

    // Test: Text anhaengen
    appendTextFile("/test.txt", "Noch eine Zeile\n");

    // Test: Datei lesen
    String sdText = readTextFile("/test.txt");
    log(INFO, "SD Inhalt", sdText);

    // Test: Dateiliste anzeigen
    listMicroSDDir("/", 1);

    log(INFO, "System gestartet");
    log(INFO, "Device ID", DEVICE_ID);
    log(INFO, "SSID", WIFI_SSID);

    // verbindet WLAN
    initWifi();

    // synchronisiert die Zeit
    initClock();

    // startet den Webserver
    initRouter();

    initOTA();

    // speichert einmal einen Demo Zeitpunkt
    demoEventMillis = millis();

    // zeigt die umgerechnete echte Zeit
    log(INFO, "Demo Event millis", demoEventMillis);
    log(INFO, "Demo Event Zeit", millisToTimeString(demoEventMillis));
}

void loop()
{
    // verarbeitet HTTP Anfragen
    updateRouter();

    // prüft WLAN Verbindung
    updateWifi();

    updateOTA();

    // verarbeitet blinkende Status LED
    updateOnLight();

    // verarbeitet Relay Trigger
    updateRelay();
}