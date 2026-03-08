#ifndef PINS_H
#define PINS_H

// ============================================================
// HARDWARE PINS
// zentrale Definition aller Hardware Pins
// ============================================================

// LED vom Arduino Nano ESP32
#define ON_STATUS_PIN 13

// Relay Ausgang auf D2
#define RELAY_PIN 2

// ------------------------------------------------------------
// microSD
// CD = Card Detect
// CS = Chip Select
// DI = Daten zum Modul
// DO = Daten vom Modul
// CLK = SPI Takt
// ------------------------------------------------------------
#define SD_CD 8
#define SD_CS 9
#define SD_DI 10
#define SD_DO 11
#define SD_CLK 12

#endif