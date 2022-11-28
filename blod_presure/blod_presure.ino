
#include <AD770X.h>

AD770X ad7706(65536);
double v =0;



double EMA_ALPHA = 0.6;
double EMA_LP = 0;
double EMA_HP = 0;
int bomba = 6;
int val = 5;
double maxPre = 0;
double presion = 0;
double maxfiltro = 0;
double filteredHP = 0;
double cero = 0;
void setup()
{
  pinMode(8, OUTPUT);
  pinMode(bomba, OUTPUT);
  pinMode(val, OUTPUT);
  Serial.begin(38400);
  ad7706.reset();
  ad7706.init(AD770X::CHN_AIN2);  
}

void loop()
{


  digitalWrite(val, HIGH);
  digitalWrite(bomba, HIGH);
  delay(5000);
  delay(5000);
  delay(3000);
  digitalWrite(bomba, LOW);

   ad7706.reset();
   ad7706.init(AD770X::CHN_AIN2);



   delay(500);

    for(int i=0; i <= 20; i++){  
      v = ad7706.readADResult(AD770X::CHN_AIN2);

      delay(10);

      ad7706.reset();
      ad7706.init(AD770X::CHN_AIN2);

       filteredHP = EMAHighPassFilter(v);

          Serial.print(v);
          Serial.print(",");
          Serial.println(filteredHP);
  }
  
    for(int i=0; i <= 120; i++){  
      v = ad7706.readADResult(AD770X::CHN_AIN2);
 
      delay(10);

      ad7706.reset();
      ad7706.init(AD770X::CHN_AIN2);

       filteredHP = EMAHighPassFilter(v);

       if (filteredHP > maxfiltro)
       {
          maxfiltro = filteredHP; 
          maxPre = v;
       }
         
          Serial.print(v);
          Serial.print(",");
          Serial.println(filteredHP);
  }
 
  delay(1000);
   v = ad7706.readADResult(AD770X::CHN_AIN2);
   Serial.println(v);
   cero = v;
  presion = (maxPre-cero)/1.18;

  Serial.print('P');
  Serial.print(',');
  Serial.print(presion);
  Serial.print('\n');
  Serial.println(cero);
  Serial.println(maxPre);

  digitalWrite(val, LOW);
  delay(5000);
  delay(5000);
  delay(5000);
  delay(5000);
}


double EMAHighPassFilter(double value)
{
   EMA_LP = EMA_ALPHA * value + (1 - EMA_ALPHA) * EMA_LP;
   EMA_HP = value - EMA_LP;
   return EMA_HP;
}
