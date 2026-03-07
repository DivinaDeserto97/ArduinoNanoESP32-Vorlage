#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

// ============================================================
// WIFI MANAGER
// verwaltet die WLAN Verbindung
// ============================================================

#include <Arduino.h>

// baut WLAN Verbindung auf
void initWifi();

// prüft regelmäßig Verbindung
void updateWifi();

// prüft ob WLAN verbunden ist
bool isWifiConnected();

// gibt Status Text zurück
String getWifiStatusText();

#endif