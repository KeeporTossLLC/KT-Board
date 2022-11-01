#include <Arduino.h>
#include <Wire.h>
/*
 *  requires the arduino Accelerometer library
 *  https://github.com/ldab/kxtj3-1057
 * 
 */

// power modes (choose one)
#define LOW_POWER
//#define HIGH_RESOLUTION

// optional debug output
#define KXTJ3_DEBUG Serial

// include library
#include "kxtj3-1057.h"

// HZ - Samples per second - 0.781, 1.563, 3.125, 6.25, 12.5, 25, 50, 100, 200, 400, 800, 1600Hz
float sampleRate = 6.25;  

// Accelerometer range = 2, 4, 8, 16g
uint8_t accelRange = 2;     

// init
KXTJ3 myIMU(0x0E);


void setup()
{
    
    Serial.begin(115200);
    delay(1000); 
    
    // I2C lines: SDA=4, SCL=7
    Wire.begin(4, 7);
    
    if( myIMU.begin(sampleRate, accelRange) != 0 )
    {
        Serial.print("Failed to initialize IMU.\n");
    }
    else
    {
        Serial.print("IMU initialized.\n");
    }
    
    // Detection threshold, movement duration and polarity
    myIMU.intConf(123, 1, 10, HIGH);
    
    uint8_t readData = 0;
    
    // Get the ID:
    myIMU.readRegister(&readData, KXTJ3_WHO_AM_I);
    Serial.print("CHIP ID: 0x");
    Serial.println(readData, HEX);

}



void loop()
{

    myIMU.standby( false );
    
    int16_t dataHighres = 0;
    
    if( myIMU.readRegisterInt16( &dataHighres, KXTJ3_OUT_X_L ) != 0 )
    {
        Serial.print(" Acceleration X RAW = ");
        Serial.println(dataHighres);
    }
    
    if( myIMU.readRegisterInt16( &dataHighres, KXTJ3_OUT_Z_L ) != 0 )
    {
    
        Serial.print(" Acceleration Z RAW = ");
        Serial.println(dataHighres);
    }
    
    // Read accelerometer data in mg as Float
    Serial.print(" Acceleration X float = ");
    Serial.println( myIMU.axisAccel( X ), 4);
    
    // Read accelerometer data in mg as Float
    Serial.print(" Acceleration Y float = ");
    Serial.println( myIMU.axisAccel( Y ), 4);
    
    // Read accelerometer data in mg as Float
    Serial.print(" Acceleration Z float = ");
    Serial.println( myIMU.axisAccel( Z ), 4);
    
    myIMU.standby( true );

    // wait for 1 sec
    delay(1000);

}
