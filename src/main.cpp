#include <Arduino.h>
#include "ESPconfig.h"
#include "ESPWifi.h"
#include "myLED.h"
#include "Wire.h"
#include "TLx493D_inc.hpp"
// #include "Mag_Sensor.h"
#include "ESPudp.h"
// #include "MCP4725.h"
#include "Signal_Gen.h"
#include "TLx493D.h"
// #include "TLX493D.h"


using namespace ifx::tlx493d;
// ifx::tlx493d::TLx493D_W2B6 dut(Wire, TLx493D_IIC_ADDR_A0_e);
TwoWire twoWire = TwoWire(0);
TwoWire twoWire1 = TwoWire(1);
ESPconfig espConfig;
MyLED myLED(&espConfig);
ESPWifi espWifi(&espConfig);
ESPnetwork espNet(&espConfig);
Signal_Gen sigGen(&espConfig, &twoWire1);
// TLx493D magSensor(twoWire, 0x22););
TLx493D_W2B6 dut(twoWire, TLx493D_IIC_ADDR_A0_e);
// Mag_Sensor magSensor(&espConfig, &dut);
// uint8_t count = 0;

void setup(){
  espConfig.progState = 0;
  myLED.startTask();
  Serial.begin(115200);
  delay(5000);
  espConfig.progState = 2;
  Serial.println("Starting up...");
  espConfig.progCfg.confRes = espConfig.loadConfig();
  twoWire.setPins(espConfig.gpioDefs.SDA_PIN, espConfig.gpioDefs.SCL_PIN);
  twoWire.setClock(100000);
  
  twoWire.begin();
  pinMode(14, OUTPUT);
  digitalWrite(14, HIGH);
  twoWire1.setPins(espConfig.gpioDefs.SDA_H_PIN, espConfig.gpioDefs.SCL_H_PIN);
  twoWire1.begin();
  espConfig.wifiCfg.state = espWifi.makeAP();
  Serial.println("Wifi State: " + String(espConfig.wifiCfg.state));
  espNet.begin();
      Serial.println("Network setup complete");
  sigGen.startTask();
 
  
  delay(1000);
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    twoWire.beginTransmission(address);
    error = twoWire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  // Serial.println(twoWire.requestFrom(0x22, 0x01));
  // if(twoWire.available()) {	      // read response from slave 0x08
	// 	Serial.println(Wire.read());
	// }
  delay(5000);
  // magSensor.startTask();
  // dut.setPowerPin(14, OUTPUT, INPUT, HIGH, LOW, 0, 250000);
  
  twoWire.beginTransmission(0x22);
  twoWire.write(0xFF);
  // twoWire.endTransmission();
  // twoWire.beginTransmission(0xFF);
  twoWire.write(0xFF);
  // twoWire.endTransmission();
  // twoWire.beginTransmission(0xFF);
  twoWire.write(0x00);
  // twoWire.endTransmission();
  // twoWire.beginTransmission(0xFF);
  twoWire.write(0x00);
  twoWire.endTransmission();
  delay(1000);
  
  // dut.set
  dut.begin(false, false, false, false);
  // dut.setPowerMode(TLx493D_PowerModeType_t::TLx493D_MASTER_CONTROLLED_MODE_e);
  
  espConfig.progState = 1;
  // magSensor.begin();
  // Tle493dMagnetic3DSensor.enableTemp();
}

void debugPrint(){
  Serial.printf("Timestamp since boot [ms]: %lu", millis());
  Serial.printf(" progName: %s", espConfig.progCfg.name);
  Serial.printf(" progState: %lu", espConfig.progState);
  Serial.printf(" confRes: %lu", espConfig.progCfg.confRes);
  Serial.printf(" wifiRes: %lu", espConfig.wifiCfg.state);
  
  Serial.println();
  // Serial.println(twoWire.requestFrom(0x22, 0x01));
  // Serial.printf("Mag x: %.2f mT, y: %.2f mT, z: %.2f mT, Temp: %.2f °C\n", espConfig.magData.x, espConfig.magData.y, espConfig.magData.z, (espConfig.magData.t*1.8)+32);
  // Serial.println();
  // Serial.println(espConfig.progCfg.name);
  // Serial.println();
}

void loop(){
  
  // please note that the value of status should be checked and properly handler
  
  delay(1000);
  debugPrint();

  
  

  double t, x, y, z;

    dut.setSensitivity(TLx493D_FULL_RANGE_e);
    // dut.getI2CAddress();
    dut.getMagneticFieldAndTemperature(&x, &y, &z, &t);
    // dut.printRegisters();

  //   Serial.print("\nTemperature is: ");
  //   Serial.print(t);
  //   Serial.println("°C");

    Serial.print("Value X is: ");
    Serial.print(x);
    Serial.println(" mT");
    Serial.print("Value Y is: ");
    Serial.print(y);
    Serial.println(" mT");
    Serial.print("Value Z is: ");
    Serial.print(z);
    Serial.println(" mT");

    // dut.setSensitivity(TLx493D_SHORT_RANGE_e);
    // dut.getMagneticFieldAndTemperature(&x, &y, &z, &t);
    // // dut.printRegisters();

    // // Serial.print("\nTemperature is: ");
    // // Serial.print(t);
    // // Serial.println("°C");

    // Serial.print("Value X is: ");
    // Serial.print(x);
    // Serial.print(" mT");
    // Serial.print(" Value Y is: ");
    // Serial.print(y);
    // Serial.print(" mT");
    // Serial.print(" Value Z is: ");
    // Serial.print(z);
    // Serial.println(" mT");
    // // Serial.print("\n\n\n\n");

    // delay(100);

    // Serial.print("count : ");
    // Serial.println(count);

    // if( ++count == 4 ) {
    //     Serial.println("\nBefore reset -------------------------------------------------------------------------------------------------------");

    //     /** Reset does not work for W2BW : either drive strength too low or delay to stabilize critical. */
    //     dut.reset(true, dut.getSensorType() != TLx493D_A1B6_e);

    //     Serial.println("\nAfter reset -------------------------------------------------------------------------------------------------------");
    //     count = 0;
    // }
}