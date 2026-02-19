# 📦 Arduino Nano ESP32 -- Projektvorlage

## 📌 Ziel dieser Vorlage

Diese Projektbasis soll:

-   sauber strukturiert sein\
-   leicht erweiterbar sein\
-   für jedes neue IoT-Projekt kopiert werden können\
-   langfristig als Standard-Grundlage dienen

------------------------------------------------------------------------

## 🔧 Hardware

-   Board: Arduino Nano ESP32
-   USB-C Verbindung\
-   WLAN & Bluetooth integriert\
-   3.3V Logik\
-   ESP32-S3 Chip

------------------------------------------------------------------------

## 📁 Projektstruktur

``` bash
ArduinoNanoESP32Vorlage/
│
├── src/
│   └── main.cpp
│
├── include/
│   └── config.h
│
├── data/                # optional (LittleFS / SPIFFS)
│
├── platformio.ini
├── .env.example
└── README.md
```

------------------------------------------------------------------------

## ⚙️ Entwicklungsumgebung

Empfohlen:

-   Visual Studio Code\
-   PlatformIO Extension

Alternativ:

-   Arduino IDE

------------------------------------------------------------------------

## 🧠 Grundkonzept dieser Vorlage

Diese Vorlage ist gedacht für:

-   WLAN-fähige IoT Projekte\
-   HTTP Server (GET / POST)\
-   Sensor-Module\
-   Display-Module\
-   SD-Karten Logging\
-   Steuerung über REST-API

Ziel:\
Saubere, wiederverwendbare Struktur für jedes neue Projekt.

------------------------------------------------------------------------

## 🌐 WLAN Konfiguration

Beispiel `secret.h`:

``` bash
WIFI_SSID=DeinWLAN
WIFI_PASSWORD=DeinPasswort

LED_ON_MS=500
LED_OFF_MS=500
```

Im Code werden die Werte über `build_flags` eingebunden.

------------------------------------------------------------------------

## 🚀 Beispiel: Minimaler Startcode

``` cpp
#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("System gestartet.");
}

void loop() {
    delay(1000);
}
```

------------------------------------------------------------------------

## 🌍 Beispiel: HTTP GET Endpoint

``` cpp
server.on("/status", HTTP_GET, []() {
    server.send(200, "application/json", "{"status":"online"}");
});
```

------------------------------------------------------------------------

## 🔌 Wichtige Pins

  Funktion   Pin
  ---------- -----
  LED        13
  I2C SDA    8
  I2C SCL    9
  SPI MOSI   11
  SPI MISO   12
  SPI SCK    13

(Pins je nach Projekt prüfen!)

------------------------------------------------------------------------

## 📡 Typische Erweiterungen

-   DHT11 / DHT22\
-   OLED Display (I2C)\
-   Relais Modul\
-   SD-Karten Modul\
-   Web Dashboard\
-   JSON API\
-   OTA Updates

------------------------------------------------------------------------

## 🔐 Sicherheit

-   Keine echten WLAN Daten committen\
-   `.env` oder `secret.h` in `.gitignore` eintragen\
-   API bei Bedarf mit Passwort schützen

------------------------------------------------------------------------

## 🧩 Erweiterbare Module (Idee)

    /status
    /on
    /off
    /pulse
    /data
    /reboot

------------------------------------------------------------------------

## 🛠 Upload

PlatformIO:

``` bash
pio run --target upload
```

Monitor:

``` bash
pio device monitor
```