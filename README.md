# 📦 Arduino Nano ESP32 -- Projektvorlage (IoT Basis)

## 📌 Ziel dieser Vorlage

Diese Projektbasis dient als **saubere und wiederverwendbare Grundlage
für IoT‑Firmware** auf dem Arduino Nano ESP32.

Die Struktur ist so aufgebaut, dass Projekte:

-   sauber strukturiert bleiben
-   modular erweitert werden können
-   mehrfach kopiert werden können
-   langfristig als persönliche **Standard‑Firmwarebasis** dienen

Ziel ist eine **robuste IoT‑Grundarchitektur** mit:

-   WLAN
-   Webserver
-   JSON API
-   Zeitverwaltung
-   Geräteidentifikation
-   Debug‑Logging

------------------------------------------------------------------------

# 🔧 Hardware

Board: **Arduino Nano ESP32**

  Eigenschaft   Beschreibung
  ------------- -----------------------
  MCU           ESP32‑S3
  Logik         3.3V
  USB           USB‑C
  Netzwerk      WLAN + Bluetooth
  Flash         je nach Boardvariante

------------------------------------------------------------------------

# 📁 Projektstruktur

    ArduinoNanoESP32/
    │
    ├── include/
    │   ├── pins.h              # zentrale Pin Definitionen
    │   ├── secretVorlage.h     # Vorlage der secret Version one daten
    │   ├── env.h            # WLAN + Geräte ID
    │   └── system_state.h      # Systemweite Variablen
    │
    ├── src/
    │
    │   ├── Debug/
    │   │   └── logger.h        # Debug Logging System
    │
    │   ├── ESP32/
    │   │
    │   │   ├── config/
    │   │   │   └── device_config.h
    │   │   │
    │   │   ├── wifi/
    │   │   │   ├── wifi_manager.h
    │   │   │   └── wifi_manager.cpp
    │   │   │
    │   │   ├── time/
    │   │   │   ├── uhr.h
    │   │   │   └── uhr.cpp
    │   │   │
    │   │   ├── web/
    │   │   │   ├── router.h
    │   │   │   ├── router.cpp
    │   │   │   └── status_page.h
    │   │   │
    │   │   ├── controller/
    │   │   │   ├── controller.h
    │   │   │   └── controller.cpp
    │   │   │
    │   │   └── main.cpp        # Startpunkt der Firmware
    │
    ├── data/                   # optional: LittleFS / SPIFFS
    │
    ├── platformio.ini
    └── README.md

------------------------------------------------------------------------

# 🧠 Architektur‑Idee

Die Firmware ist in **Module aufgeteilt**:

  Modul        Aufgabe
  ------------ ----------------------
  Debug        Logging System
  wifi         WLAN Verbindung
  time         Zeitverwaltung + NTP
  web          HTTP Server
  controller   API Datenlogik
  config       Gerätekonfiguration
  include      Hardware & Secrets
  main         Firmware Startpunkt

Diese Struktur verhindert **spaghetti code** und erlaubt später einfache
Erweiterungen.

------------------------------------------------------------------------

# ⏱ Zeitarchitektur (millis + echte Zeit)

Ein wichtiger Teil dieser Vorlage ist die **Zeit‑Verknüpfung zwischen
`millis()` und echter Uhrzeit**.

Beim ersten erfolgreichen NTP Sync wird gespeichert:

    bootEpoch  = echte Zeit (Unix Zeit)
    bootMillis = millis() zum gleichen Zeitpunkt

Damit kann jede gespeicherte `millis` Zeit später berechnet werden:

    eventEpoch = bootEpoch + (eventMillis - bootMillis) / 1000

Vorteile:

-   nur `millis()` speichern
-   wenig RAM
-   wenig Flash
-   auch ohne RTC möglich

Beispiel:

    unsigned long buttonPress = millis();
    Serial.println(millisToTimeString(buttonPress));

------------------------------------------------------------------------

# 🌐 Webserver

Der ESP32 startet einen kleinen HTTP Server.

  Route       Beschreibung
  ----------- -------------------------
  `/`         schöne HTML Statusseite
  `/status`   JSON API

### Beispiel JSON

    {
     "device_id":"00/ArduinoNanoESP32",
     "boot_time":"07.03.2026 12:33:36",
     "current_time":"07.03.2026 12:36:12",
     "uptime_ms":185000,
     "wifi":{
      "connected":true,
      "ip":"192.168.50.11",
      "rssi":-67
     },
     "system":{
      "heap":278584,
      "cpu_mhz":240
     }
    }

------------------------------------------------------------------------

# 🖥 Statusseite

Die Startseite zeigt eine kleine **Geräte‑Dashboardseite**:

-   Device ID
-   Boot Zeit
-   aktuelle Zeit
-   Uptime
-   WLAN Status
-   Signalstärke
-   Heap Speicher

------------------------------------------------------------------------

# 📡 WLAN Konfiguration

Datei:

    include/env.h

Beispiel:

    #define DEVICE_ID "00/ArduinoNanoESP32"

    #define WIFI_SSID "DeinWLAN"
    #define WIFI_PASSWORD "DeinPasswort"

Diese Datei sollte **nicht ins Git Repository**.

------------------------------------------------------------------------

# 🔌 Wichtige Pins

  Funktion   Pin
  ---------- -----
  LED        13
  I2C SDA    8
  I2C SCL    9
  SPI MOSI   11
  SPI MISO   12
  SPI SCK    13

Pins können je nach Boardvariante abweichen.

------------------------------------------------------------------------

# 📡 Typische Erweiterungen

Diese Architektur ist vorbereitet für:

-   Sensoren
-   Relaissteuerung
-   Web Dashboard
-   REST API
-   Datenlogging
-   MQTT
-   OTA Updates

Beispiel API Erweiterungen:

    /status
    /on
    /off
    /pulse
    /data
    /reboot

------------------------------------------------------------------------

# 🔐 Sicherheit

Empfehlungen:

-   `env.h` in `.gitignore`
-   API optional mit Token schützen
-   getrennte Gäste‑WLAN Geräte

------------------------------------------------------------------------

# 🛠 Upload

Firmware flashen:

    pio run --target upload

Serial Monitor:

    pio device monitor

------------------------------------------------------------------------

# 🚀 Ziel dieser Vorlage

Diese Vorlage soll langfristig eine **universelle ESP32‑Firmwarebasis**
sein.

Neue Projekte starten dann einfach mit:

    cp -r ArduinoNanoESP32Vorlage NeuesProjekt

und können sofort erweitert werden.