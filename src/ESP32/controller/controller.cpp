// ============================================================
// CONTROLLER IMPLEMENTATION
// baut JSON Status Antwort
// ============================================================

#include "controller.h"

#include <WiFi.h>
#include <esp_system.h>

#include "../../../include/env.h"
#include "../config/device_config.h"
#include "../wifi/wifi_manager.h"
#include "../time/uhr.h"

// baut JSON Status
String buildStatusJson()
{
    String json = "{";

    json += "\"device_id\":\"" + String(DEVICE_ID) + "\",";
    json += "\"device_name\":\"" + String(DEVICE_NAME) + "\",";
    json += "\"boot_time\":\"" + getBootTimeString() + "\",";
    json += "\"current_time\":\"" + getSwissTimeString() + "\",";
    json += "\"uptime_ms\":" + String(millis()) + ",";
    json += "\"uptime_seconds\":" + String(getUptimeSeconds()) + ",";
    json += "\"boot_epoch\":" + String((unsigned long)getBootEpoch()) + ",";
    json += "\"boot_millis\":" + String(getBootMillis()) + ",";

    json += "\"wifi\":{";
    json += "\"connected\":" + String(isWifiConnected() ? "true" : "false") + ",";
    json += "\"status\":\"" + getWifiStatusText() + "\",";
    json += "\"ip\":\"" + WiFi.localIP().toString() + "\",";
    json += "\"rssi\":" + String(WiFi.RSSI());
    json += "},";

    json += "\"system\":{";
    json += "\"heap\":" + String(ESP.getFreeHeap()) + ",";
    json += "\"cpu_mhz\":" + String(getCpuFrequencyMhz()) + ",";
    json += "\"web_port\":" + String(WEB_SERVER_PORT);
    json += "}";

    json += "}";

    return json;
}