#KT-IOT-BOARD

## Arduino library for IOT Board development

Handles interaction with the KT-BOARD

Supports;
- Arduino
- PlatformIO


## Hardware
Hardware is available at : http://tindie.com/site

KT-BOARD Hardware includes an ESP32-C3 and an Quectel BG95-M3 modem.
(supported pcb version: QT-KT-1000)

## Examples
See examples folder for code showing how to use the library.

- Quectel 4G Cell Modem serial client example
- Motor Controller
- Basic board usage
- Accelerometer
- Port Expander


## Getting Started

- download zip file
- unzip kt-board folder
- open an example from the examples folder to start coding and testing.

## Arduino IDE Settings
- device uses USB CDC
- see image : images/Arduino_IDE_settings.png
  - Important;
  - Board selection : "ESP32C3 Dev Module"
  - USB CDC On Boot : "Enabled"

## Dependencies

- Requires Arduino ESP32 board core version 2.04 or greater. (to support ESP32-C3 chipset)
  - getting started guide to setup Arduino IDE: https://docs.espressif.com/projects/arduino-esp32/en/latest/getting_started.html

- Requires PCAL9535A library from https://github.com/chrissbarr/PCAL9535A-Arduino-Library

- In order to use the 4G Cell Network
  - requires a 4G service provider + SIM Card, code examples use the Hologram service.
