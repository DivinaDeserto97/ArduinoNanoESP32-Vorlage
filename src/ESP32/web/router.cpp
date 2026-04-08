// ============================================================
// ROUTER IMPLEMENTATION
// HTTP Server und API Routing
// ============================================================

#include "router.h"

#include <WebServer.h>

#include "../../Debug/logger.h"
#include "../config/device_config.h"
#include "../controller/controller.h"
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
    server.onNotFound(handleNotFound);

    server.begin();

    log(SUCCESS, "Webserver gestartet");
    log(INFO, "HTML", "/");
    log(INFO, "JSON", STATUS_ROUTE);
}

// verarbeitet requests
void updateRouter()
{
    server.handleClient();
}