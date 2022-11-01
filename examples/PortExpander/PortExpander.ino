#include <Arduino.h>
#include <Wire.h>
#include "PCAL9535A.h"

/*
 *  requires PCAL9535A library
 *  https://github.com/chrissbarr/PCAL9535A-Arduino-Library
 */

PCAL9535A::PCAL9535A<TwoWire> gpio(Wire);
  
void setup() 
{  
  
    Serial.begin(115200);
    Serial.println("Starting Port Expander example...");

    // I2C lines: SDA=4, SCL=7
    Wire.begin(4, 7);
    gpio.begin();

}

void loop() {

    printAllGPIO();  
    delay(500);

}

void printAllGPIO() 
{
    int state = gpio.readGPIO16(); 
     
    for (int i = 0; i < 16; i++) 
    {
      bool b = state & (1 << 15);
      Serial.print(b);
      state = state << 1;
    }
    
    Serial.println();

}
