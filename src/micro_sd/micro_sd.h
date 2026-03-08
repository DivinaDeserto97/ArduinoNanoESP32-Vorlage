#ifndef MICRO_SD_H
#define MICRO_SD_H

// ============================================================
// MICRO SD
// verwaltet die micro SD Karte und Dateioperationen
// ============================================================

#include <Arduino.h>

// startet die micro SD Karte
bool initMicroSD();

// prueft ob die SD erfolgreich gestartet wurde
bool isMicroSDReady();

// prueft ueber den Card Detect Pin ob eine Karte steckt
bool isMicroSDInserted();

// gibt Infos ueber die SD im Log aus
void printMicroSDInfo();

// listet Dateien in einem Ordner auf
void listMicroSDDir(const char* path = "/", uint8_t levels = 0);

// schreibt eine Datei neu
bool writeTextFile(const char* path, const String& content);

// ueberschreibt eine Datei komplett
bool overwriteTextFile(const char* path, const String& content);

// haengt Text an eine Datei an
bool appendTextFile(const char* path, const String& content);

// liest eine Textdatei komplett
String readTextFile(const char* path);

// loescht eine Datei
bool deleteFile(const char* path);

// prueft ob eine Datei existiert
bool fileExists(const char* path);

// gibt die Dateigroesse zurueck
size_t getFileSize(const char* path);

#endif