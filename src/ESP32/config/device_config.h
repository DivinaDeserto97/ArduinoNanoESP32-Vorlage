#ifndef DEVICE_CONFIG_H
#define DEVICE_CONFIG_H

// ============================================================
// GERÄTE KONFIGURATION
// feste Einstellungen für dieses Gerät
// ============================================================

// Anzeigename im Netzwerk
#define DEVICE_NAME "NanoESP32-01"

// Webserver Port
#define WEB_SERVER_PORT 80

// API Route für JSON Status
#define STATUS_ROUTE "/status"

// LED Zeiten
#define LED_ON_TIME_MS 100
#define LED_OFF_TIME_MS 400

// WLAN Überprüfung Intervall
#define WIFI_CHECK_INTERVAL_MS 10000

#endif