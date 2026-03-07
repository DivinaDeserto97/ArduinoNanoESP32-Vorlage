#ifndef STATUS_PAGE_H
#define STATUS_PAGE_H

// ============================================================
// STATUS PAGE
// erzeugt eine schöne HTML Statusseite
// ============================================================

#include <Arduino.h>
#include <WiFi.h>

#include "../time/uhr.h"
#include "../wifi/wifi_manager.h"
#include "../../../include/secret.h"

// formatiert Sekunden als lesbare Uptime
inline String formatUptimePretty(unsigned long totalSeconds)
{
    unsigned long days = totalSeconds / 86400;
    unsigned long hours = (totalSeconds % 86400) / 3600;
    unsigned long minutes = (totalSeconds % 3600) / 60;
    unsigned long seconds = totalSeconds % 60;

    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%lu Tage %02lu:%02lu:%02lu", days, hours, minutes, seconds);

    return String(buffer);
}

// erstellt HTML Statusseite
inline String buildStatusPage()
{
    String html = "";

    html += "<!DOCTYPE html>";
    html += "<html lang='de'>";
    html += "<head>";
    html += "<meta charset='UTF-8'>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<title>ESP32 Status</title>";

    html += "<style>";
    html += "body{margin:0;padding:24px;background:#0f1115;color:#e8eaed;font-family:Arial,sans-serif;}";
    html += ".wrap{max-width:900px;margin:0 auto;}";
    html += "h1{margin:0 0 20px 0;color:#7cc7ff;}";
    html += ".grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(240px,1fr));gap:16px;}";
    html += ".box{background:#171b22;border:1px solid #2a313d;border-radius:12px;padding:16px;box-shadow:0 4px 14px rgba(0,0,0,0.25);}";
    html += ".title{font-size:18px;font-weight:bold;color:#7cc7ff;margin-bottom:12px;}";
    html += ".row{margin:8px 0;}";
    html += ".label{display:inline-block;min-width:110px;color:#a9b4c2;}";
    html += ".ok{color:#64d98b;font-weight:bold;}";
    html += ".bad{color:#ff7d7d;font-weight:bold;}";
    html += ".small{margin-top:20px;color:#91a0b3;font-size:13px;}";
    html += "a{color:#7cc7ff;text-decoration:none;}";
    html += "</style>";

    html += "</head>";
    html += "<body>";
    html += "<div class='wrap'>";

    html += "<h1>ESP32 STATUS</h1>";

    html += "<div class='grid'>";

    // Gerät
    html += "<div class='box'>";
    html += "<div class='title'>Gerät</div>";
    html += "<div class='row'><span class='label'>Device ID:</span> " + String(DEVICE_ID) + "</div>";
    html += "<div class='row'><span class='label'>Boot Zeit:</span> " + getBootTimeString() + "</div>";
    html += "<div class='row'><span class='label'>Jetzt:</span> " + getSwissTimeString() + "</div>";
    html += "<div class='row'><span class='label'>Uptime:</span> " + formatUptimePretty(getUptimeSeconds()) + "</div>";
    html += "</div>";

    // WLAN
    html += "<div class='box'>";
    html += "<div class='title'>WLAN</div>";
    html += "<div class='row'><span class='label'>Verbunden:</span> ";
    html += isWifiConnected() ? "<span class='ok'>Ja</span>" : "<span class='bad'>Nein</span>";
    html += "</div>";
    html += "<div class='row'><span class='label'>Status:</span> " + getWifiStatusText() + "</div>";
    html += "<div class='row'><span class='label'>IP:</span> " + WiFi.localIP().toString() + "</div>";
    html += "<div class='row'><span class='label'>Signal:</span> " + String(WiFi.RSSI()) + " dBm</div>";
    html += "</div>";

    // System
    html += "<div class='box'>";
    html += "<div class='title'>System</div>";
    html += "<div class='row'><span class='label'>Heap:</span> " + String(ESP.getFreeHeap()) + " bytes</div>";
    html += "<div class='row'><span class='label'>CPU:</span> " + String(getCpuFrequencyMhz()) + " MHz</div>";
    html += "<div class='row'><span class='label'>Millis:</span> " + String(millis()) + "</div>";
    html += "</div>";

    html += "</div>";

    html += "<div class='small'>JSON API: <a href='/status'>/status</a></div>";

    html += "</div>";
    html += "</body>";
    html += "</html>";

    return html;
}

#endif