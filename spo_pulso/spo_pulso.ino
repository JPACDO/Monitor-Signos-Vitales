
#include <Wire.h>
#include "MAX30105.h"

MAX30105 particleSensor;

#define debug Serial //Uncomment this line if you're using an Uno or ESP
//#define debug SerialUSB //Uncomment this line if you're using a SAMD21
int led = 13;
long a = 0;
int temp = 0;  
int value = 0;

void setup()
{
  debug.begin(38400);
  debug.println("MAX30105 Basic Readings Example");

  // Initialize sensor
  if (particleSensor.begin() == false)
  {
    debug.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }


  
  byte ledBrightness = 60; //Options: 0=Off to 255=50mA
  byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  byte sampleRate = 100; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 411; //Options: 69, 118, 215, 411
  int adcRange = 4096; //Options: 2048, 4096, 8192, 16384

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
  
  while (Serial.available() == 0) ; //wait until user presses a key
  Serial.read();
}

void loop()
{
  digitalWrite(led, HIGH);
  debug.print("B,");
  debug.print(particleSensor.getRed());
  debug.print(",");
  debug.print(particleSensor.getIR());
  debug.print('\n');
  digitalWrite(led, LOW);
  delay(1);

  temp = analogRead(A0);
        //temp = (value * 500)/1023;
        Serial.print('C');
        Serial.print(temp);
        Serial.print('\n');

}
