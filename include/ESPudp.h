#ifndef ESPNETWORK_H
#define ESPNETWORK_H

#include "Arduino.h"
#include "AsyncUDP.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "ESPconfig.h"


class ESPnetwork{
    public:
        void begin();
        void sendUDP();
        void updateDebugVars();
        void handleDebugVars(AsyncWebServerRequest *request);
        ESPnetwork(ESPconfig* vars);
    private:
        std::vector<String> debugVars;
        AsyncUDP udp;
        AsyncWebServer server;
        ESPconfig* espConfig;
    
};

#endif