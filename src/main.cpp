// ============================================================
// MAIN PROGRAM
// startet das System und ruft alle Module im loop auf
// ============================================================

#include <Arduino.h>

#include "../include/pins.h"
#include "../include/env.h"
#include "../include/system_state.h"

#include "./Debug/logger.h"

#include "./ESP32/config/device_config.h"
#include "./ESP32/on_light/on_light.h"
#include "./ESP32/time/uhr.h"
#include "./ESP32/web/router.h"
#include "./ESP32/wifi/wifi_manager.h"
#include "./ESP32/ota/ota_manager.h"
#include "./micro_sd/micro_sd.h"

void setup()
{
    Serial.begin(115200);
    delay(500);

    log(INFO, "Systemstart");
    log(INFO, "Device ID", DEVICE_ID);
    log(INFO, "Device Name", DEVICE_NAME);

    initOnLight();

    initMicroSD();

    if (isMicroSDReady())
    {
        writeTextFile("/test.txt", "Hallo von der micro SD\n");
        appendTextFile("/test.txt", "Noch eine Zeile\n");
        log(INFO, "SD Inhalt", readTextFile("/test.txt"));
    }

    initWifi();
    initClock();
    initRouter();
    initOTA();

    log(SUCCESS, "Setup abgeschlossen");
}

void loop()
{
    updateRouter();
    updateWifi();
    updateOTA();
    updateOnLight();
}