// ============================================================
// ROUTER IMPLEMENTATION
// HTTP Server und API Routing
// ============================================================

#include "router.h"

#include <WebServer.h>

#include "../../../include/system_state.h"
#include "../../../include/secret.h"
#include "../../Debug/logger.h"
#include "../../micro_sd/micro_sd.h"
#include "../config/device_config.h"
#include "status_page.h"

static WebServer server(WEB_SERVER_PORT);

// root route
void handleRoot()
{
    server.send(200, "text/html; charset=utf-8", buildStatusPage());
}

// status api
void handleStatus()
{
    bool sdReady = isMicroSDReady();
    bool sdInserted = isMicroSDInserted();
    bool testFileExists = false;
    String testFileContent = "";

    if (sdReady)
    {
        testFileExists = fileExists("/test.txt");

        if (testFileExists)
        {
            testFileContent = readTextFile("/test.txt");
        }
    }

    String json = "{";

    json += "\"device_id\":\"" + String(DEVICE_ID) + "\",";
    json += "\"boot_time\":\"" + getBootTimeString() + "\",";
    json += "\"current_time\":\"" + getSwissTimeString() + "\",";
    json += "\"uptime_ms\":" + String(millis()) + ",";

    json += "\"wifi\":{";
    json += "\"connected\":" + String(isWifiConnected() ? "true" : "false") + ",";
    json += "\"status\":\"" + getWifiStatusText() + "\",";
    json += "\"ip\":\"" + WiFi.localIP().toString() + "\",";
    json += "\"rssi\":" + String(WiFi.RSSI());
    json += "},";

    json += "\"micro_sd\":{";
    json += "\"inserted\":" + String(sdInserted ? "true" : "false") + ",";
    json += "\"ready\":" + String(sdReady ? "true" : "false") + ",";
    json += "\"test_file_exists\":" + String(testFileExists ? "true" : "false");

    if (sdReady && testFileExists)
    {
        json += ",";
        json += "\"test_file_size\":" + String((unsigned long)getFileSize("/test.txt")) + ",";
        json += "\"test_file_content\":\"";

        // einfache JSON Maskierung
        for (size_t i = 0; i < testFileContent.length(); i++)
        {
            char c = testFileContent[i];

            if (c == '\\') json += "\\\\";
            else if (c == '\"') json += "\\\"";
            else if (c == '\n') json += "\\n";
            else if (c == '\r') json += "\\r";
            else json += c;
        }

        json += "\"";
    }

    json += "}";

    json += "}";

    server.send(200, "application/json; charset=utf-8", json);
}

// relay test route
void handleRelayPulse()
{
    relayPulseRequest = true;
    server.send(200, "text/plain; charset=utf-8", "Relay Puls angefordert");
}

// unbekannte Route
void handleNotFound()
{
    server.send(404, "text/plain; charset=utf-8", "Route nicht gefunden");
}

// startet server
void initRouter()
{
    server.on("/", handleRoot);
    server.on(STATUS_ROUTE, handleStatus);
    server.on("/relay/pulse", handleRelayPulse);
    server.onNotFound(handleNotFound);

    server.begin();

    log(SUCCESS, "Webserver gestartet");
    log(INFO, "HTML", "/");
    log(INFO, "JSON", STATUS_ROUTE);
    log(INFO, "Relay Puls", "/relay/pulse");
}

// verarbeitet requests
void updateRouter()
{
    server.handleClient();
}