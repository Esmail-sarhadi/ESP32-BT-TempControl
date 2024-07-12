#include "BluetoothSerial.h"
#include <DHT.h>

BluetoothSerial SerialBT;

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float numHumidity;
float numTemperature;

//GPIO where LED is connected to.
int pinRelay = 5;

//Handle received and sent messages.
String incomingMessage = "";
char incomingChar;
String outcomingMessage = "";
char outcomingChar;
String temphumidString = "";

//Timer: auxiliar variables
unsigned long previousMillis = 0;                   //Stores last time temperature was published.
const long interval = 10000;                        //Interval at which to publish sensor readings.

//REPLACE WITH RECEIVER MAC Address.
//24:0A:C4:31:6D:92
uint8_t address[6]  = {0x24, 0x0A, 0xC4, 0x31, 0x6D, 0x92};

String name = "ESP32Slave1";
//char *pin = "12343212122";                               //Standard pin would be provided by default.
bool connected;
//*********************************************************************************
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32Slave", true);
  //SerialBT.setPin(pin);
  Serial.println(">> The device started in master mode, make sure remote BT device is on!");

  dht.begin();

  //Connect(address) is fast (upto 10 secs max), connect(name) is slow (upto 30 secs max) as it needs
  //to resolve name to address first, but it allows to connect to different devices with the same name.
  //Set CoreDebugLevel to Info to view devices bluetooth address and device names

  connected = SerialBT.connect(address);
  //connected = SerialBT.connect(name);

  if (connected) {
    Serial.println(">> Connected Succesfully!");
  } else {
    while (!SerialBT.connected(10000)) {
      Serial.println(">> Failed to connect. Make sure remote device is available and in range, then restart app.");
    }
  }
  //Disconnect() may take upto 10 secs max.
  if (SerialBT.disconnect()) {
    Serial.println(">> Disconnected Succesfully!");
  }

  //This would reconnect to the name(will use address, if resolved) or address used with connect(name/address).
  if (SerialBT.connect(address)) Serial.println(">> Connected Succesfully!");

  pinMode(pinRelay, OUTPUT);
}
//*********************************************************************************
void loop() {
  unsigned long currentMillis = millis();
  //Send temperature readings.
  if (currentMillis - previousMillis >= interval) {
    numHumidity = dht.readHumidity();
    numTemperature = dht.readTemperature();
    previousMillis = currentMillis;
    temphumidString = ">> Temperature: " + String(numTemperature) + "C  " + "Humidity: " +  String(numHumidity) + "%";
    Serial.println(temphumidString);
    SerialBT.println(temphumidString);
  }

  if (SerialBT.available()) {
    incomingChar = SerialBT.read();
    if (incomingChar != '\n') {
      incomingMessage += String(incomingChar);
      //Check received message and control output accordingly.
      if (incomingMessage == "Relay_on") {
        Serial.println(">> Relay is on.");
        digitalWrite(pinRelay, HIGH);
      }
      else if (incomingMessage == "Relay_off") {
        Serial.println(">> Relay is off.");
        digitalWrite(pinRelay, LOW);
      }
    }
    else {
      incomingMessage = "";
    }
  }

  delay(20);
}
//*********************************************************************************
