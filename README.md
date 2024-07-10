# ESP32-BT-TempControl

This project implements a Bluetooth-based temperature monitoring and relay control system using an ESP32 microcontroller. It consists of two main components: a master device and a slave device.
![Alt text](senario.jpg)
## Features

- Bluetooth communication between ESP32 devices
- Temperature and humidity monitoring using DHT11 sensor
- Remote relay control
- Periodic sensor data transmission

## Hardware Requirements

- 2x ESP32 development boards
- DHT11 temperature and humidity sensor
- Relay module
- Appropriate power supply

## Software Dependencies

- Arduino IDE
- ESP32 board support for Arduino
- BluetoothSerial library
- DHT sensor library

## Installation

1. Install the Arduino IDE and ESP32 board support.
2. Install the required libraries:
   - BluetoothSerial (comes with ESP32 board support)
   - DHT sensor library
3. Clone this repository or download the source code.
4. Open the `.ino` files in Arduino IDE.

## Configuration

### Master Device

- Set the Bluetooth device name in `SerialBT.begin("ESP32Master")`.
- Optionally, set a PIN code by uncommenting and modifying the `pin` variable.

### Slave Device

- Set the Bluetooth device name in `SerialBT.begin("ESP32Slave", true)`.
- Configure the MAC address of the master device in the `address` array.
- Set the DHT sensor pin in `#define DHTPIN 4`.
- Set the relay control pin in `int pinRelay = 5`.

## Usage

1. Upload the master code to one ESP32 and the slave code to another.
2. Power on both devices.
3. The master device will automatically try to connect to the slave.
4. Once connected, the slave will start sending temperature and humidity data every 10 seconds.
5. Send "Relay_on" or "Relay_off" from the master device to control the relay on the slave device.

## Contributing

Contributions to improve the project are welcome. Please feel free to submit a Pull Request.

## License

This project is open-source and available under the [MIT License](LICENSE).
