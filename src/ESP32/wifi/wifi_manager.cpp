// ============================================================
// WIFI MANAGER IMPLEMENTATION
// verbindet und überwacht WLAN
// ============================================================

#include "wifi_manager.h"

#include <WiFi.h>

#include "../../Debug/logger.h"
#include "../../../include/env.h"
#include "../config/device_config.h"

// speichert letzten Prüfzeitpunkt
static unsigned long lastWifiCheck = 0;

// gibt lesbaren WLAN Status zurück
String getWifiStatusText()
{
    switch (WiFi.status())
    {
        case WL_IDLE_STATUS:
            return "idle";

        case WL_NO_SSID_AVAIL:
            return "ssid nicht gefunden";

        case WL_SCAN_COMPLETED:
            return "scan abgeschlossen";

        case WL_CONNECTED:
            return "verbunden";

        case WL_CONNECT_FAILED:
            return "verbindung fehlgeschlagen";

        case WL_CONNECTION_LOST:
            return "verbindung verloren";

        case WL_DISCONNECTED:
            return "getrennt";

        default:
            return "unbekannt";
    }
}

// baut WLAN Verbindung auf
void initWifi()
{
    WiFi.mode(WIFI_STA);
    WiFi.setHostname(DEVICE_NAME);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    log(INFO, "Verbinde WLAN", WIFI_SSID);

    int retry = 0;

    while (WiFi.status() != WL_CONNECTED && retry < 30)
    {
        delay(500);
        Serial.print(".");
        retry++;
    }

    Serial.println();

    if (WiFi.status() == WL_CONNECTED)
    {
        log(SUCCESS, "WLAN verbunden");
        log(INFO, "IP", WiFi.localIP().toString());
        log(INFO, "MAC", WiFi.macAddress());
        log(INFO, "RSSI", WiFi.RSSI());
    }
    else
    {
        log(ERROR, "WLAN Verbindung fehlgeschlagen");
    }

    lastWifiCheck = millis();
}

// prüft regelmäßig WLAN
void updateWifi()
{
    unsigned long currentMillis = millis();

    // erkennt millis overflow
    if (currentMillis < lastWifiCheck)
    {
        log(WARN, "millis overflow bei WLAN Check");
        lastWifiCheck = 0;
    }

    // wartet bis das Prüfintervall erreicht ist
    if (currentMillis - lastWifiCheck < WIFI_CHECK_INTERVAL_MS)
    {
        return;
    }

    lastWifiCheck = currentMillis;

    // beendet wenn WLAN noch verbunden ist
    if (WiFi.status() == WL_CONNECTED)
    {
        return;
    }

    log(WARN, "WLAN getrennt reconnect");

    WiFi.disconnect();
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

// prüft Verbindung
bool isWifiConnected()
{
    return WiFi.status() == WL_CONNECTED;
}