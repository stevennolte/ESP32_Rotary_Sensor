#include "ESPWifi.h"
#include "WiFi.h"


ESPWifi::ESPWifi(ESPconfig* vars){
    espConfig = vars;
}

uint8_t ESPWifi::connect(){
    IPAddress local_IP(espConfig->wifiCfg.ips[0],espConfig->wifiCfg.ips[1],espConfig->wifiCfg.ips[2],espConfig->wifiCfg.ips[3]);
    IPAddress gateway(espConfig->wifiCfg.ips[0],espConfig->wifiCfg.ips[1],espConfig->wifiCfg.ips[2],1);
    IPAddress subnet(255,255,255,0);
    uint8_t numNetworks = WiFi.scanNetworks();
    for (int i = 0; i < numNetworks; i++){
        for (int j = 0; j < 4; j++){
            if (WiFi.SSID(i) == espConfig->wifiCfg.ssids[j]){
                WiFi.begin(espConfig->wifiCfg.ssids[j],espConfig->wifiCfg.passwords[j]);
                WiFi.config(local_IP,gateway,subnet);
                return 1;
            }
        }
    }
    return 1;
}

uint8_t ESPWifi::makeAP(){
    IPAddress local_IP(espConfig->wifiCfg.ips[0],espConfig->wifiCfg.ips[1],espConfig->wifiCfg.ips[2],espConfig->wifiCfg.ips[3]);
    IPAddress gateway(espConfig->wifiCfg.ips[0],espConfig->wifiCfg.ips[1],espConfig->wifiCfg.ips[2],1);
    IPAddress subnet(255,255,255,0);
    WiFi.mode(WIFI_AP);   
    WiFi.softAP(espConfig->progCfg.name, "1234567890");
    delay(100);
    WiFi.softAPConfig(local_IP, local_IP, subnet);
    return 3;
}

void ESPWifi::startMonitor(){
    xTaskCreate(
        taskHandler,   // Task function
        "TaskB",       // Name of the task
        4096,          // Stack size (in words)
        this,          // Pass the current instance as the task parameter
        1,             // Priority of the task
        NULL           // Task handle (not needed)
    );
}

void ESPWifi::taskHandler(void *param){
    ESPWifi* instance = (ESPWifi*)param;
    instance->continuousLoop();
}

void ESPWifi::continuousLoop(){
    while (true){
        if (!WiFi.isConnected()){
           connect();
        }
    vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    
}