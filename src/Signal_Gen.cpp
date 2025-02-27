#include "Signal_Gen.h"


Signal_Gen::Signal_Gen(ESPconfig* vars, TwoWire* wire) : dac(0x60, wire) {
    espConfig = vars;
    twoWire = wire;
    dac = MCP4725(0x60, twoWire);
}

void Signal_Gen::startTask() {
    if(dac.begin()){
        Serial.println("DAC connected");
    } else {
        Serial.println("DAC not connected");
    };
}