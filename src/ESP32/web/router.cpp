// ============================================================
// ROUTER IMPLEMENTATION
// HTTP Server und API Routing
// ============================================================

#include "router.h"

#include <WebServer.h>

#include "../../../include/system_state.h"
#include "../../Debug/logger.h"
#include "../controller/controller.h"
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
    server.send(200, "application/json; charset=utf-8", buildStatusJson());
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