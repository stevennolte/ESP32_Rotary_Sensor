#ifndef ESPCONF_H
#define ESPCONF_H
#include "Arduino.h"
#include "LittleFS.h"
#include "ArduinoJson.h"
#include "Version.h"

class ESPconfig
{
public:
    uint8_t loadConfig();
    uint8_t getStrapping();
    uint8_t progState;
    class GPIO_Definitions{
        public:
            uint8_t LED_PIN = 48;
            uint8_t SDA_PIN = 41;
            uint8_t SCL_PIN = 42;
            uint8_t SDA_H_PIN = 5;
            uint8_t SCL_H_PIN = 6;
            
            
            GPIO_Definitions(){}
    };
    GPIO_Definitions gpioDefs;

    class I2C_Definitions{
        public:
            uint8_t TLE_ADDRESS = 0x22;
            uint8_t MCP_ADDRESS = 0x20;
            I2C_Definitions(){}
    };
    I2C_Definitions i2cDefs;

    class ProgramConfig {
        public:
            char name[64];
            String name2;
            uint8_t version[3];
            uint8_t ledBrht;
            uint8_t confRes;
            uint8_t magState;
            uint8_t dacState;
            ProgramConfig(){}
    };
    ProgramConfig progCfg;
    
    class WifiConfig {
        public:
            const char* ssids[4];
            const char* passwords[4];
            uint8_t ips[4];
            uint8_t state;
            WifiConfig(){}
    };
    WifiConfig wifiCfg;

    class OTAConfig {
        public:
            uint8_t state;
            uint8_t port;
            uint8_t ipAddr[4];
            char basePath[64];
            OTAConfig(){}
    };
    OTAConfig otaCfg;

    class MagConfig {
        public:
            uint8_t sensitivity;
            MagConfig(){}
    };

    class MagData {
        public:
            double x;
            double y;
            double z;
            double t;
            MagData(){}
    };
    MagData magData;

    ESPconfig(/* args */);
    
    
};




#endif
