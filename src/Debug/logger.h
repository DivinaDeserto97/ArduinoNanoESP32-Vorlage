#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

// ===== Log-Level Definition =====
// Hier legst du fest, welche Arten von Logs es gibt
enum LogLevel {
    INFO,       // normale Information
    SUCCESS,    // erfolgreich abgeschlossen
    WARN,       // Warnung
    ERROR,      // Fehler
    DEBUG       // Entwickler-Information
};

// ===== ANSI Farben für Terminal =====
// Funktioniert im PlatformIO Monitor (nicht im Arduino IDE Monitor)
#define COLOR_RESET  "\033[0m"
#define COLOR_RED    "\033[31m"
#define COLOR_GREEN  "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE   "\033[34m"
#define COLOR_CYAN   "\033[36m"

// ===== Log ohne Variable =====
// Beispiel: log(INFO, "System gestartet");
inline void log(LogLevel level, const String &message) {

    String prefix;
    const char* color;

    // Je nach Log-Level Farbe + Text setzen
    switch(level) {

        case INFO:
            prefix = "[INFO] ";
            color = COLOR_BLUE;
            break;

        case SUCCESS:
            prefix = "[SUCCESS] ";
            color = COLOR_GREEN;
            break;

        case WARN:
            prefix = "[WARN] ";
            color = COLOR_YELLOW;
            break;

        case ERROR:
            prefix = "[ERROR] ";
            color = COLOR_RED;
            break;

        case DEBUG:
            prefix = "[DEBUG] ";
            color = COLOR_CYAN;
            break;

        default:
            prefix = "[LOG] ";
            color = COLOR_RESET;
    }

    Serial.print(color);        // Farbe setzen
    Serial.print(prefix);       // z.B. [INFO]
    Serial.print(message);      // dein Text
    Serial.println(COLOR_RESET); // Farbe zurücksetzen
}


// ===== Log mit Variable =====
// Beispiel: log(INFO, "Temperatur", temperatur);
template <typename T>
inline void log(LogLevel level, const String &message, T variable) {

    String prefix;
    const char* color;

    switch(level) {

        case INFO:
            prefix = "[INFO] ";
            color = COLOR_BLUE;
            break;

        case SUCCESS:
            prefix = "[SUCCESS] ";
            color = COLOR_GREEN;
            break;

        case WARN:
            prefix = "[WARN] ";
            color = COLOR_YELLOW;
            break;

        case ERROR:
            prefix = "[ERROR] ";
            color = COLOR_RED;
            break;

        case DEBUG:
            prefix = "[DEBUG] ";
            color = COLOR_CYAN;
            break;

        default:
            prefix = "[LOG] ";
            color = COLOR_RESET;
    }

    Serial.print(color);
    Serial.print(prefix);
    Serial.print(message);
    Serial.print(" : ");
    Serial.print(variable);      // Variable ausgeben
    Serial.println(COLOR_RESET);
}

#endif
