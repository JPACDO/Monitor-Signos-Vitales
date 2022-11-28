/*
 * AD770X Library
 * sample code (AD7706)
 * Kerry D. Wong
 * http://www.kerrywong.com
 * 3/2011
 */

#include <AD770X.h>

AD770X ad7706(65536);
double v;
double EMA_ALPHA = 0.15;
double EMA_LP = 0;
double EMA_HP = 0;
double filteredHP = 0;
const int LED = 7;

void setup()
{
    pinMode(LED, OUTPUT);
  Serial.begin(38400);
   while (Serial.available() == 0) ; //wait until user presses a key
  Serial.read();
  ad7706.reset();
  ad7706.init(AD770X::CHN_AIN1);  
  ad7706.init(AD770X::CHN_AIN2);
 v = ad7706.readADResult(AD770X::CHN_AIN1);
 filteredHP = EMAHighPassFilter(v);


}

void loop()
{
  digitalWrite(LED, HIGH);
  v = ad7706.readADResult(AD770X::CHN_AIN2);
  filteredHP = EMAHighPassFilter(v);
  if(filteredHP > 29910){
  Serial.print('R');
  Serial.print(',');
  Serial.print(filteredHP);
  Serial.print('\n');
  }
  delay(5);
  digitalWrite(LED, LOW);
    ad7706.reset();
  //ad7706.init(AD770X::CHN_AIN1);  
  ad7706.init(AD770X::CHN_AIN2);
  delay(5);
}


double EMAHighPassFilter(double value)
{
   EMA_LP = EMA_ALPHA * value + (1 - EMA_ALPHA) * EMA_LP;
   //EMA_HP = value - EMA_LP;
   return EMA_LP;
}
