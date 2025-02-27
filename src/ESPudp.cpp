#include "ESPudp.h"


ESPnetwork::ESPnetwork(ESPconfig* vars) : udp(), server(80) {
    espConfig = vars;
}

void ESPnetwork::begin(){
    udp.listen(8888);
    udp.onPacket([this](AsyncUDPPacket packet) {
        if (packet.data()[0]==0x80 && packet.data()[1]==0x81){
        //   espConfig.udpTimer = millis();
          switch (packet.data()[3]){
            case 201:
              
              this->espConfig->wifiCfg.ips[0] = packet.data()[7];
              this->espConfig->wifiCfg.ips[1] = packet.data()[8];
              this->espConfig->wifiCfg.ips[2] = packet.data()[9];
            //   config.updateConfig();
              ESP.restart();
              break;
          }
        }
    });
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(LittleFS, "/index.html");
    });
    server.on("/getDebugVars", HTTP_GET, [this](AsyncWebServerRequest *request) {
        this->handleDebugVars(request);
    });
    server.begin();
}

void ESPnetwork::updateDebugVars() {
    //TODO: add more debug variables
  debugVars.clear(); // Clear the list to update it dynamically
  debugVars.push_back("Timestamp since boot [ms]: " + String(millis()));
  debugVars.push_back("Free Heap: " + String(ESP.getFreeHeap()) + " bytes");
  debugVars.push_back("Version: " + String(VERSION));
  std::string ipValue = "Sensor: " + std::to_string(WiFi.localIP());
}

void ESPnetwork::handleDebugVars(AsyncWebServerRequest *request) {
  updateDebugVars();  // Update the debug variables just before sending
  JsonDocument doc;
  JsonArray array = doc.to<JsonArray>();
  
  for (const auto& var : debugVars) {
    array.add(var);
  }
  
  String jsonResponse;
  serializeJson(doc, jsonResponse);
  request->send(200, "application/json", jsonResponse);
}

void ESPnetwork::sendUDP() {
}