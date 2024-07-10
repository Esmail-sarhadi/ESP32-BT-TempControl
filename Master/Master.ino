#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

//char *pin = "1234";                                         //Standard pin would be provided by default.
//*********************************************************************************
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32Master");                              //Bluetooth device name.
  //SerialBT.setPin(pin);
  Serial.println(">> The device started, now you can pair it with bluetooth!");
}
//*********************************************************************************
void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
}
//*********************************************************************************
