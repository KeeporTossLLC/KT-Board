#include <HardwareSerial.h>
#include <Wire.h>
#include "PCAL9535A.h"

/*
 *  requires PCAL9535A library
 *  https://github.com/chrissbarr/PCAL9535A-Arduino-Library
 */
 
HardwareSerial HWSerial(1);

PCAL9535A::PCAL9535A<TwoWire> gpio(Wire);
 
#define RXD2 1
#define TXD2 3

/*
 *  LTE MODEM connection example and passthru serial 
 * 
 *  Once running, you can send AT commands via serial monitor.
 *  
 *  Example is for Hologram service
 * 
 */

void device_power_on()
{
     // turn on power
    Serial.println("Turning on power...");
    pinMode(6, OUTPUT);
    digitalWrite(6,LOW);
    delay(100); 
    digitalWrite(6,HIGH); 
    delay(100);  
}
void modem_power_on()
{
    // modem power on sequence
    gpio.digitalWrite(15, LOW);
    delay(1000);
    Serial.println("Trigger modem power...");
    gpio.digitalWrite(15, HIGH);
    delay(1000);
    gpio.digitalWrite(15, LOW);
    Serial.println("Modem initialized...");
}

void setup() 
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("LTE Modem example starting");
    delay(2000);
    
    Serial.println("Initialise UART...");
    HWSerial.begin(115200, SERIAL_8N1, RXD2, TXD2);
    
    Serial.println("Initializing modem...");
  
    // I2C lines: SDA=4, SCL=7
    Wire.begin(4, 7);
    gpio.begin();  
    gpio.pinMode(15, OUTPUT);
    
    
    device_power_on();

    modem_power_on();
    
    Serial.println("listening...");
}

String power_down_response = "POWER DOWN";
String app_ready_response = "APP RDY";

String frozen_response = "a\r\n";

bool sent_connect_command = false;
bool check_status = true;

int check_count = 0;
 
void loop() 
{
    if (HWSerial.available())
    {  
      
        String buffer = "";
        while (HWSerial.available())
        { 
            buffer += String(char(HWSerial.read()));
        }
        
        Serial.println(buffer);  
        if (buffer.indexOf(app_ready_response) != -1)
        {
            Serial.println("found App Ready");
            // got app ready, start connection
            sent_connect_command = true;
        }
        
        
        if (buffer.indexOf(frozen_response) != -1)
        {
            Serial.println("found Frozen Response... reset.");
            modem_power_on();
            delay(1000);
            
        } else if (buffer.indexOf(power_down_response) != -1)
        {
            Serial.println("found Power Down");
        }
    }
    
    delay(100);


    if (sent_connect_command)
    {
    
        sent_connect_command = false;
        check_status = true;
        delay(3000);
        Serial.println("sending AT command...");
        HWSerial.write("AT+CFUN=0\r\n");
        delay(1000);
        
        HWSerial.write("AT+QCFG=\"servicedomain\",2,1\r\n");
        delay(500);
        HWSerial.write("AT+QCFG=\"nwscanmode\",3,1\r\n");
        delay(500);
        HWSerial.write("AT+QCFG=\"nwscanseq\",02,1\r\n");
        delay(500);
        HWSerial.write("AT+QCFG=\"iotopmode\",0,1\r\n");
        
        delay(500);
        HWSerial.write("AT+CFUN=1\r\n");
        
        delay(1000);
        Serial.println("sending AT command...");
        //HWSerial.write("AT+CGDCONT=1,\"IP\",\"hologram\",\"0.0.0.0\",0,0,0\r\n");   
        HWSerial.write("AT+CGDCONT=1,\"IP\",\"hologram\"\r\n");  
       

    }
        
    if (check_status) 
    {
        delay(1000);
        check_count++;
        HWSerial.write("AT+QCSQ\r\n");  
        Serial.print("[");
        Serial.print(check_count);
        Serial.println("]");  
    }

    if (Serial.available()) 
    {     
        HWSerial.write(Serial.read());   
    }
  
}
